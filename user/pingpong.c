#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    int pid = fork();
    if(pid > 0) {
    //进入父进程 pid = child's pid
    write(p1[1],"!",1);
    char buf;
    read(p2[0],&buf,1);
    printf("%d: received pong\n",getpid());
    wait(&pid);  
    } else if(pid == 0) {
        char buf;
        read(p1[0],&buf,1);
        printf("%d: received ping\n",getpid());
        write(p2[1],"!",1);
    }
    else {
         printf("fork error\n");
    }
    exit(0);

}