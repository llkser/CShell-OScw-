#include "myShell.h"

int main()
{
    char CWdir[255];
    CWdir[0]='\0';
    int flag;

    flag=readlink("/proc/self/exe",CWdir,255);
    if(flag<0||flag>=PATH_MAX)
    {
        printf("Error!\n");
        return 0;
    }
    else{
        int i;
        for(i=strlen(CWdir)-1;i>=0;i--)
            if(CWdir[i]=='/')
            {
                CWdir[i]='\0';
                break;
            }
    }

    while (1)
    {
        printf("[myShell@llkser]$$ ");
        char ucmd[255];
        gets(ucmd);
        if(exeCmd(parseCmd(ucmd),ucmd,CWdir)==0)
            break;
    }
    
    return 0;
}