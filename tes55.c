#include <stdio.h>
#include <syslog.h>
#include <string.h>

int
main ()
{
    char *mesg = "hello world.";

    //syslog(LOG_WARNING, mesg);

//      openlog(mesg, LOG_PID, LOG_AUTH);

    char buf[50];

    getcwd (buf, sizeof (buf));

    printf ("buf: %s\nsize:%d\nstrlen: %d\n", buf, sizeof (buf), strlen (buf));

    char *dir = "/var/log";

    chdir (dir);
    getcwd (buf, sizeof (buf));
    printf ("buf: %s\n", buf);

    printf ("'\\n': %d\n", '\0');

    char bufs[80];

    strcpy (bufs, "hello");
    printf ("buf: %s\n", bufs);
    strcat (bufs, "world");
    printf ("buf: %s\n", bufs);

    return 0;
}
