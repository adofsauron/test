#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int
main (int argc, char **argv)
{
  if (argc < 3)
    {
      printf ("error!");
      exit (0);
    }

  char *ip = argv[1];
  int port = atoi (argv[2]);

  int servfd = socket (AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serv_addr;

  bzero (&serv_addr, sizeof (serv_addr));

  serv_addr.sin_family = AF_INET;
  inet_pton (AF_INET, ip, &serv_addr.sin_addr);
  serv_addr.sin_port = htons (port);

  int flag;

  flag = connect (servfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr));

  char buf[128];
  char *msg = "hello world.";
  strcpy (buf, msg);

  send (servfd, msg, strlen (msg), 0);

  close (servfd);

  return 0;

}
