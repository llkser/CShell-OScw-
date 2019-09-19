#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>
#include <cstring>

int exeCmd(int,char*);
int parseCmd(char*);
int strMatcher(char*);

#endif