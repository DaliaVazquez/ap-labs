#define _XOPEN_SOURCE 500
#define MAX_EVENTS 1000 
#define LEN_NAME 20
#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN (10*(sizeof(struct inotify_event)+100))
#include <stdio.h>
#include "logger.h"
#include <ftw.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/inotify.h>
int inotifyFd,n=0; 

static int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {
    if(tflag==FTW_D){
        n = inotify_add_watch(inotifyFd, fpath, IN_MOVE | IN_CREATE | IN_DELETE);
        if(n==-1){
            errorf("Error inotify");
        }  
    }
    return 0;
}

int main(int argc, char **argv){
    // Place your magic here
    if(argc!=2){
        warnf("Incorrect number of arguments.\n");
        return 0;
    }
    inotifyFd=inotify_init();
    if(inotifyFd== -1){
        panicf("inotify_init");
        return 0;
    } 
    char *dir;
    dir=argv[1];  
    initLogger("stdout");  
    int flags=0;
    if (nftw(dir, display_info, 20, flags) != -1) {
        printf("Starting File/Directory Monitor on %s\n", dir);
        printf("-----------------------------------------------------\n");
    }else{
       errorf("Error");
       return 0;
    }
    ssize_t numr;
    char buf[BUF_LEN];
    while(1){;
        numr=read(inotifyFd, buf, BUF_LEN);
        if(numr==0){
            panicf("error\n");
            return 0;
        }else if(numr==-1){
            errorf("Error: read\n");
            return 0;
        }
        int i=0;
        while (i < numr) {
            struct inotify_event *event=(struct inotify_event*)&buf[i];
            if(event->len){
                if(event-> mask & IN_CREATE){
                    if(event-> mask & IN_ISDIR){
                        infof("- [Directory - Create] - %s\n", event->name);
                    }else{
                        infof("- [File - Create] - %s\n", event->name);
                    }
                }else if (event->cookie!=0){
                    if(event->mask & IN_MOVED_FROM){
                        if(event-> mask & IN_ISDIR){
                            infof("- [Directory - Rename] - %s -> ", event->name);
                        }else{
                            infof("- [File - Rename] - %s -> ", event->name);
                        }
                    } else infof("%s\n",event->name);
                }else if(event-> mask & IN_DELETE){
                    if(event-> mask & IN_ISDIR){
                        infof("- [Directory - Removal] - %s\n", event->name);
                    }else{
                        infof("- [File - Removal] - %s\n", event->name);
                    }
                }else{
                    infof("error: action");
                }
                i+=EVENT_SIZE+event->len;
            }
        }
    }
    inotify_rm_watch( inotifyFd, n );
    close( inotifyFd );
    return 0;
}
