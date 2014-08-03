#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void showHostent(struct hostent *h)
{
  printf ("h_name: %s\n", h->h_name);
  printf ("h_aliases: %s\n", h->h_aliases[0]);
  printf ("h_addrtype: %d\n", h->h_addrtype);
  printf ("h_length: %d\n", h->h_length);
  struct in_addr *inaddr;
  inaddr = (struct in_addr *) h->h_addr;
  printf ("IP Address: %x\n", inaddr->s_addr);
}

int
htconnect (char *domain, int port)
{
  int white_sock;
  struct hostent *site;
  struct sockaddr_in me;
  site = gethostbyname (domain);
  if (site == NULL)
    return -2;
  white_sock = socket (AF_INET, SOCK_STREAM, 0);

  if (white_sock < 0)
    return -1;
  memset (&me, 0, sizeof (struct sockaddr_in));
  memcpy (&me.sin_addr, site->h_addr_list[0], site->h_length);
  me.sin_family = AF_INET;
  me.sin_port = htons (port);


  showHostent(site);

  return (connect
	  (white_sock, (struct sockaddr *) &me,
	   sizeof (struct sockaddr)) < 0) ? -1 : white_sock;
}

int
htsend (int sock, char *fmt, ...)
{
  char BUF[1024];
  va_list argptr;
  va_start (argptr, fmt);
  vsprintf (BUF, fmt, argptr);
  va_end (argptr);
  return send (sock, BUF, strlen (BUF), 0);
}

void
writeio (int sockfd)
{
  const char *filename = "tmp.html";
  char buff[3];
  int fd = open (filename, O_RDWR | O_CREAT);
  if (!fd)
    {
      printf ("error!\n");
      return;
    }
  chmod (filename, S_IROTH | S_IWOTH);
  while (read (sockfd, buff, 1) > 0)
    {
 //   printf("%c", buff[0]);
      write (fd, buff, 1);
    }


  close (fd);
}

void
main (int argc, char **argv)
{
  int black_sock;
  char bugs_bunny[3];
  if (argc < 2)
    return;
  black_sock = htconnect (argv[1], 80);
  if (black_sock < 0)
    return;
    
  htsend (black_sock, "GET / HTTP/1.0%c", '\n');
  htsend (black_sock, "Host: %s%c", argv[1], 10);
  htsend (black_sock, "%c", 10);


  writeio (black_sock);

  close (black_sock);
}
