#include "myShell.h"

int main()
{
    char CWdir[255];
    CWdir[0]='\0';
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