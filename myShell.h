#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>
#include <dirent.h>
#include <string.h>

int exeCmd(int,char*,char*);
int parseCmd(char*);
void strMatcher(char*,char*);
int* paiComputor(char*);
void execFile(char*,char*);

#endif