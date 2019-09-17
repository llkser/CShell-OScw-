#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>

int exeCmd(int);
int parseCmd(char*);

#endif