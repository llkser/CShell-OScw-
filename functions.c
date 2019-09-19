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
        if(ucmd[0]=='g'&&ucmd[1]=='r'&&ucmd[2]=='e'&&ucmd[3]=='p'&&ucmd[4]==' '&&ucmd[5]=='-'&&ucmd[6]=='c'&&ucmd[7]==' ')
            choice=3;
        else
            choice=-1;
        break;
    }

    return choice;
}

int exeCmd(int choice, char* ucmd)
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
        break;
    case 3:
        strMatcher(ucmd);
        break;
    default:
        break;
    }
    return 1;
}

int strMatcher(char* ucmd)
{

}