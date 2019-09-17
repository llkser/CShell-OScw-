#include "myShell.h"

int main()
{
    while (1)
    {
        printf("[myShell@llkser]$$ ");
        char ucmd[255];
        gets(ucmd);
        if(exeCmd(parse(ucmd))==0)
            break;
    }
    
    return 0;
}