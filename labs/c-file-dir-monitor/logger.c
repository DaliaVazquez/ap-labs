#define RESET 0
#define BRIGHT 1
#define DIM 2
#define UNDERLINE 3
#define BLINK 4
#define REVERSE 7
#define HIDDEN 8
#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define	WHITE 7
#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include "logger.h"
bool sys=false;

void textcolor(int attr, int fg)
{	char command[13];
	sprintf(command, "%c[%d;%dm", 0x1B, attr, fg + 30);
	printf("%s", command);
}

void printl(int priority,const char *format,va_list args){
    if(!sys){
        vprintf(format, args);
    }else{
        openlog("logger", LOG_PID | LOG_CONS, LOG_SYSLOG);
        vsyslog(priority, format, args);
        closelog();
    }
}

int initLogger(char *logType) {
    textcolor(RESET,GREEN);
    if(strcmp(logType, "syslog") == 0) {
        sys=true;
    }else if(strcmp(logType, "stdout") == 0) {
        sys=false;
    } 
    printf("Initializing Logger on: %s\n", logType);
    printf("%c[0m",0x1B);
    return 0;
}

int infof(const char *format, ...){
    textcolor(RESET,BLUE);
    va_list args;
    va_start(args,format);
    printl(LOG_INFO,format,args);
    va_end(args);
    printf("%c[0m",0x1B);
}

int warnf(const char *format, ...){
    textcolor(RESET,YELLOW);
    va_list args;
    va_start(args,format);
    printl(LOG_WARNING,format,args);
    va_end(args);
    printf("%c[0m",0x1B);
}

int errorf(const char *format, ...){
    textcolor(RESET,RED);
    va_list args;
    va_start(args,format);
    printl(LOG_ERR,format,args);
    va_end(args);
    printf("%c[0m",0x1B);
}

int panicf(const char *format, ...){
    textcolor(RESET,MAGENTA);
    va_list args;
    va_start(args,format);
    printl(LOG_EMERG,format,args);
    va_end(args);
    printf("%c[0m",0x1B);
    raise(SIGABRT);
}