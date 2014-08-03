/* ¿Í»§¶Ë³ÌÐò */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

char buf[80];
char rec_buf[80];
struct sockaddr myname;
main(){
  int   sock, adrlen, cnt;
  sock = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock < 0) {
    printf("client socket failure %d\n", errno);
    perror("client: ");
    exit(1);  }
  myname.sa_family = AF_UNIX;
  strcpy(myname.sa_data, "/tmp/billb");
  adrlen = strlen(myname.sa_data) +
      sizeof(myname.sa_family);
  if (connect( sock, &myname, adrlen) < 0) {
    printf("client connect failure %d\n", errno);
    perror("client: ");
    exit(1);
  }  /*  . . . . .  */

  strcpy(buf, "Message sent to server");
  cnt = write(sock, buf, strlen(buf));
  
  bzero(buf, sizeof(buf));
  cnt = read(sock, buf, strlen(buf));
  printf("Client with pid %d got message %s\n", getpid(), buf);
  printf("Socket address in server %d is %x, %s\n",
     getpid(), myname.sa_data, myname.sa_data);
  /*  . . . . .  */
  exit(0);
}
