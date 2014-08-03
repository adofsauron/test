/* 服务器端程序 */
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>

struct sockaddr myname;
char buf[80];


main()
{
  int sock, new_sd, adrlen, cnt;
  sock = socket(AF_UNIX, SOCK_STREAM, 0);		/* 套接字的建立 */
  if (sock < 0) {
    printf("server socket failure %d\n", errno);
    perror("server: ");
    exit(1);  }
  myname.sa_family = AF_UNIX;
  strcpy(myname.sa_data, "/tmp/billb");
  adrlen = strlen(myname.sa_data) + sizeof(myname.sa_family);
  unlink("/tmp/billb");  /* defensive programming */
  if (bind(sock, &myname, adrlen) < 0) {
    printf("server bind failure %d\n", errno);
    perror("server: ");
    exit(1);  }
  if (listen(sock, 5) < 0) {		/* listen函数调用 */
    printf("server listen failure %d\n", errno);
    perror("server: ");
    exit(1);  }  

  /* 忽略子进程的终止  */
  signal (SIGCHLD, SIG_IGN);
  /*  将服务器置于死循环状态，等待客户端的连接请求的到来。
      实际上，应该用更好的办法来结束这个死循环，在这里这
      个循环是被连接开始信号或者是超级用户终止的。     */

  while (1) {
    if (new_sd = accept(sock, &myname, &adrlen) < 0) {
      printf("server accept failure %d\n", errno);
      perror("server: ");
      exit(1);    }

    /* 建立服务器端子进程。此时父进程将不再运行
       --它返回循环状态等待下一个连接请求     */

    printf("Socket address in server %d is %x, %s\n",
      getpid(), myname.sa_data, myname.sa_data);

    if (fork() == 0) {  /* 建立子进程 */
      close (sock);  /* 关闭套接字，因为子进程不再需要它  */
      /*  . . . . .  */

      cnt = read(new_sd, buf, strlen(buf));
      /* read函数读取套接字缓冲区中的数据到应用缓冲区*/
      printf ("Server with pid %d got message %s\n", getpid(), buf);
      strcpy (buf, "Message to client\n");
      cnt = write(new_sd, buf, strlen(buf));
      printf("cnt: %d\n", cnt);
      printf("buf: %s\n", buf);
      printf("Socket address in server %d is %x, %s\n",
        getpid(), myname.sa_data, myname.sa_data);
      /*  . . . . .  */
   
      close (new_sd); /* close prior to exiting  */
      
      printf("---------------------------------------------------\n");
      exit(0);
    }  
    
    
  }  
}
