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
        if(strlen(CWdir))
            printf("%s\n",CWdir);
        else{
            char dir[PATH_MAX];
            int flag;
            flag=readlink("/proc/self/exe",dir,PATH_MAX);
            if(flag<0||flag>=PATH_MAX)
                printf("Error!\n");
            else{
                int i;
                for(i=PATH_MAX-1;i>=0;i--)
                    if(dir[i]=='/')
                    {
                        dir[i]='\0';
                        break;
                    }
                printf("%s\n",dir);
            }
        }
        break;
    case 3:
        strMatcher(ucmd,CWdir);
        break;
    case 4:
        int i;
        for(i=3;i<strlen(ucmd);i++)
            CWdir[i-3]=ucmd[i];
        CWdir[i-3]='\0';
        break;
    case 5:
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
    
    if(strlen(CWdir))
    {
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
    }
    else{
        stream=fopen(address,"r");
        if(stream==NULL)
        {
            printf("File not exists!\n");
            return;
        }
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

    int m,q,sum;
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
