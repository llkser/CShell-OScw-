#include "myShell.h"

int parseCmd(char* ucmd)
{
    int choice;

    switch (strlen(ucmd))
    {
    case 4:
        if(ucmd[0]=='i'&&ucmd[1]=='n'&&ucmd[2]=='f'&&ucmd[3]=='o')
            choice=1;
        else if(ucmd[0]=='e'&&ucmd[1]=='x'&&ucmd[2]=='i'&&ucmd[3]=='t')
            choice=0;
        else
            choice=-1;
        break;
    case 3:
        if(ucmd[0]=='p'&&ucmd[1]=='w'&&ucmd[2]=='d')
            choice=2;
        else
            choice=-1;
        break;
    default:
        if(strlen(ucmd)>8&&ucmd[0]=='g'&&ucmd[1]=='r'&&ucmd[2]=='e'&&ucmd[3]=='p'&&ucmd[4]==' '&&ucmd[5]=='-'&&ucmd[6]=='c'&&ucmd[7]==' ')
            choice=3;
        else if(strlen(ucmd)>3&&ucmd[0]=='c'&&ucmd[1]=='d'&&ucmd[2]==' ')
            choice=4;
        else if(strlen(ucmd)>3&&ucmd[0]=='e'&&ucmd[1]=='x'&&ucmd[2]==' ')
            choice=5;
        else
            choice=-1;
        break;
    }

    return choice;
}

int exeCmd(int choice, char* ucmd, char* CWdir)
{
    switch (choice)
    {
    case -1:
        printf("Undefined command!\n");
        break;
    case 0:
        printf("Bye!\n");
        return 0;
    case 1:
        printf("XJCO2211 Simplified Shell by LLKSER.\n");
        break;
    case 2:
        printf("%s\n",CWdir);
        break;
    case 3:
        strMatcher(ucmd,CWdir);
        break;
    case 4:
        int i;
        for(i=3;i<strlen(ucmd);i++)
            CWdir[i-3]=ucmd[i];
        CWdir[i-3]='\0';
        printf("Current working direction changed!\n");
        break;
    case 5:
        execFile(ucmd,CWdir);
        break;
    }
    return 1;
}

void strMatcher(char* ucmd,char* CWdir)
{
    int i,j,n;
    char pattern[255];
    char address[255];
    char CWaddress[255];
    char text[2555];
    char ch;
    FILE *stream;

    j=0;
    for(i=8;i<strlen(ucmd);i++)
    {
        if(ucmd[i]==' ')
        {
            pattern[j]='\0';
            break;
        }
        else{
            pattern[j]=ucmd[i];
            j++;
        }
    }
	n=strlen(pattern);
    int *paiFun=(int*)malloc((n+1)*sizeof(int));
    paiFun=paiComputor(pattern);

    i++;
    j=0;
    for(i;i<strlen(ucmd);i++)
    {
        address[j]=ucmd[i];
        j++;
    }
    address[j]='\0';
    
    int p,q;
    for(p=0;p<strlen(CWdir);p++)
        CWaddress[p]=CWdir[p];
    CWaddress[p]='/';
    for(q=p+1;q<p+1+strlen(address);q++)
        CWaddress[q]=address[q-p-1];
    CWaddress[q]='\0';
    stream=fopen(CWaddress,"r");
    if(stream==NULL)
    {
        printf("File not exists!\n");
        return;
    }
    
    i=0;
    while(true)
    {
        ch=fgetc(stream);
        if(ch==EOF)
        {
            text[i]='\0';
            break;
        }
        text[i]=ch;
        i++;
    }
    fclose(stream);

    int m,sum;
    q=0;
    sum=0;
    m=strlen(text);
    for(i=0;i<m;i++)
    {
        while(q>0&&pattern[q]!=text[i])
            q=paiFun[q];
        if(pattern[q]==text[i])
            q++;
        if(q==n)
        {
            sum++;
            q=paiFun[q];
        }
    }
    printf("%d\n",sum);
    return;
}

int* paiComputor(char* pattern)
{
    int len=strlen(pattern);
    int *paiFun=(int*)malloc((len+1)*sizeof(int));
    int k=0;
    paiFun[0]=0;
	paiFun[1]=0;
    int i;
    for(i=2;i<len+1;i++)
    {
        while(k>0&&pattern[k]!=pattern[i-1])
            k=paiFun[k];
        if(pattern[k]==pattern[i-1])
            k++;
        paiFun[i]=k;
    }
    return paiFun;
}

void execFile(char* ucmd,char* CWdir)
{
    char progA[255];
    char addressA[255];
    char args[255];
    int i,j,k,fd,refd;
    pid_t pid;

    for(i=3;i<strlen(ucmd);i++)
    {
        if(ucmd[i]==' ')
            break;
        progA[i-3]=ucmd[i];
    }
    progA[i-3]='\0';
    i++;

    for(k=0;k<strlen(CWdir);k++)
        addressA[k]=CWdir[k];
    addressA[k]='/';
    k++;
    for(k;k<strlen(CWdir)+strlen(progA)+1;k++)
        addressA[k]=progA[k-strlen(CWdir)-1];
    addressA[k]='\0';

    if(ucmd[i]=='|');
    else if(ucmd[i]=='>')
    {
        i+=2;
        for(k=0;k<strlen(CWdir);k++)
            args[k]=CWdir[k];
        args[k]='/';
        k++;
        while(ucmd[i]!='\0')
        {
            args[k]=ucmd[i];
            k++;
            i++;
        }
        args[k]='\0';
        pid=fork();
        if(pid==0)
        {
            fd=open(args,O_WRONLY|O_CREAT,0777);
            refd=dup2(fd,fileno(stdout));
            if(execl(addressA,progA,NULL)==-1)
                printf("Error!\n");
            close(fd);
        }
        wait(NULL);
    }
    else{
        for(j=i;j<strlen(ucmd);j++)
            args[j-i]=ucmd[j];
        args[j-i]='\0';
        pid=fork();
        if(pid==0)
            if(execl(addressA,progA,args,NULL)==-1)
                printf("Error!\n");
        wait(NULL);
    }
}