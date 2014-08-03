/* �������˳��� */
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
  sock = socket(AF_UNIX, SOCK_STREAM, 0);		/* �׽��ֵĽ��� */
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
  if (listen(sock, 5) < 0) {		/* listen�������� */
    printf("server listen failure %d\n", errno);
    perror("server: ");
    exit(1);  }  

  /* �����ӽ��̵���ֹ  */
  signal (SIGCHLD, SIG_IGN);
  /*  ��������������ѭ��״̬���ȴ��ͻ��˵���������ĵ�����
      ʵ���ϣ�Ӧ���ø��õİ취�����������ѭ������������
      ��ѭ���Ǳ����ӿ�ʼ�źŻ����ǳ����û���ֹ�ġ�     */

  while (1) {
    if (new_sd = accept(sock, &myname, &adrlen) < 0) {
      printf("server accept failure %d\n", errno);
      perror("server: ");
      exit(1);    }

    /* �������������ӽ��̡���ʱ�����̽���������
       --������ѭ��״̬�ȴ���һ����������     */

    printf("Socket address in server %d is %x, %s\n",
      getpid(), myname.sa_data, myname.sa_data);

    if (fork() == 0) {  /* �����ӽ��� */
      close (sock);  /* �ر��׽��֣���Ϊ�ӽ��̲�����Ҫ��  */
      /*  . . . . .  */

      cnt = read(new_sd, buf, strlen(buf));
      /* read������ȡ�׽��ֻ������е����ݵ�Ӧ�û�����*/
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
