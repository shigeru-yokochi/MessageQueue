#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void *thread_func(void *param)
{
  int pid;
  pthread_t thread_id;
  thread_id = pthread_self();
  fprintf(stderr , "thread_func called\n");
  fprintf(stderr , "  thread ID = %ld\n" , thread_id);
  pid = getpid();
  fprintf(stderr , "  2:pid=%d\n" , pid);
}

int main(int argc, char *argv[])
{
  pthread_t thread;
  int pid;

  fprintf(stderr , "---Program start---\n");
  pid = getpid();
  fprintf(stderr , "1:pid = %d\n" , pid);
  if(pthread_create(&thread , NULL , thread_func , NULL) !=0)  /*2番目の引数にNULLを指定することによりスレッドの属性にデフォルトとする*/
        perror("pthread_create()");
  fprintf(stderr , "Next line of pthread_create() called. thread ID=%ld\n" , thread);
  pthread_join(thread , NULL);  /*thread_func()スレッドが終了するのを待機する。thread_func()スレッドが終了していたら、この関数はすぐに戻る*/
  
  return EXIT_SUCCESS;
}