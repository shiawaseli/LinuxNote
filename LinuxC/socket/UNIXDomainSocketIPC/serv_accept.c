#include <stddef.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

int serv_accept(int listenfd, uid_t *uidptr)
{
    int clifd, err, rval;
    socklen_t len;
    struct sockaddr_un un;
    struct stat statbuf;

    len = sizeof (un);
    if ((clifd = accept(listenfd, (struct sockaddr*)&un, &len)) < 0)
        return -1; /* often errno=EINTR, if signal caught */

    /* obtain the client's uid from its calling address */
    len -= offsetof(struct sockaddr_un, sun_path); /* len of pathname */
    un.sun_path[len] = 0; /* null terminate */

    if (stat(un.sun_path, &statbuf) < 0) {
        rval = -2;
        goto errout;
    }
    if (S_ISSOCK(statbuf.st_mode) == 0) {
        rval = -3; /* not a socket */ 
        goto errout;
    }
    if (uidptr != NULL)
        *uidptr = statbuf.st_uid; /* return uid of caller */
    unlink(un.sun_path); /* we're done with pathname now */
    return (clifd);

errout:
    err = errno;
    close(clifd);
    errno = err;
    return (rval);
}
