#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// 

void re_pipe(int pipe_id) {
    int p[2]; 
    pipe(p);
    // 读取左边的线程管道的第一个质数
    int first_value;
    read(pipe_id,&first_value,sizeof(int));
    printf("prime %d\n",first_value);
        

    // 读取左边
    int value;
    while(read(pipe_id,&value,sizeof(int))) {
        if(value % first_value) {
            write(p[1],&value,sizeof(int));
        }
    }
    int pid = fork();
    if(pid > 0) {
       wait(&pid);
               
    } else {
        re_pipe(p[0]);
    }
          
    close(p[1]);
    close(pipe_id);
    wait(0);
    exit(0);
}
int main(int argc, char *argv[]) {
    int p1[2];
    pipe(p1);
    for(int i = 2;i <= 35;i++) {
        write(p1[1],&i,sizeof(int));
    }
    
    int pid = fork();
    if(pid > 0) {
        wait(&pid);
    } else {
        re_pipe(p1[0]); // 传入左边线程的读端
    }
    exit(0);
}