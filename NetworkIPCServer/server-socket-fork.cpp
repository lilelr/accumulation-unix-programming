#include "../NetworkIPCSockets/apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif


int
initserver(int type, const struct sockaddr *addr, socklen_t alen,
           int qlen)
{
    int fd, err;
    int reuse = 1;

    if ((fd = socket(addr->sa_family, type, 0)) < 0)
        return(-1);
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse,
                   sizeof(int)) < 0) {
        err = errno;
        goto errout;
    }
    if (bind(fd, addr, alen) < 0) {
        err = errno;
        goto errout;
    }
    if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if (listen(fd, qlen) < 0) {
            err = errno;
            goto errout;
        }
    }
    return(fd);

    errout:
    close(fd);
    errno = err;
    return(-1);
}

void
serve(int sockfd)
{
    int		clfd, status;
    pid_t	pid;

    for (;;) {
        clfd = accept(sockfd, NULL, NULL);
        if (clfd < 0) {
            syslog(LOG_ERR, "ruptimed: accept error: %s",
                   strerror(errno));
            exit(1);
        }
        if ((pid = fork()) < 0) {
            syslog(LOG_ERR, "ruptimed: fork error: %s",
                   strerror(errno));
            exit(1);
        } else if (pid == 0) {	/* child */
            /*
             * The parent called daemonize ({Prog daemoninit}), so
             * STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO
             * are already open to /dev/null.  Thus, the call to
             * close doesn't need to be protected by checks that
             * clfd isn't already equal to one of these values.
             */
            if (dup2(clfd, STDOUT_FILENO) != STDOUT_FILENO ||
                dup2(clfd, STDERR_FILENO) != STDERR_FILENO) {
                syslog(LOG_ERR, "ruptimed: unexpected error");
                exit(1);
            }
            close(clfd);
//            execl("/usr/bin/uptime", "uptime", (char *)0);
//            execl("/bin/hostname", "hostname", (char *)0);

//            syslog(LOG_ERR, "ruptimed: unexpected return from exec: %s",
//                   strerror(errno));

//            int fd;
//            void* buf[512];
//            int nread_num;
//            int read_times =0;
//            if((fd=open("/home/lilelr/HappyNewYear",O_RDONLY)) >= 0){
//                while (true){
//                    nread_num = read(fd,buf,512);
//                    read_times++;
//                    if(nread_num!=0){
//                        write(STDOUT_FILENO,buf,nread_num);
//                        if(nread_num!=512){
//
////                            close(STDOUT_FILENO);
//                            break;
//                        }
//                    }
//                }
//                close(fd);
//            }
            printf("I'm B_ubuntu.Who are you?\n");
            exit(0);
        } else {		/* parent */
            close(clfd);
            waitpid(pid, &status, 0);
        }
    }
}

int
main(int argc, char *argv[])
{
    struct addrinfo	*ailist, *aip;
    struct addrinfo	hint;
    int				sockfd, err, n;
    char			*host;

    if (argc != 1)
        printf("usage: ruptimed");
#ifdef _SC_HOST_NAME_MAX
    n = sysconf(_SC_HOST_NAME_MAX);
	if (n < 0)	/* best guess */
#endif
    n = HOST_NAME_MAX;
    host = static_cast<char *>(malloc(n));
    if (host == NULL)
        printf("malloc error");
    if (gethostname(host, n) < 0)
        printf("gethostname error");
    printf("ruptimed");
    hint.ai_flags = AI_CANONNAME;
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(host, "nfs", &hint, &ailist)) != 0) {
        syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
               gai_strerror(err));
        exit(1);
    }
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
                                 aip->ai_addrlen, QLEN)) >= 0) {
            serve(sockfd);
            exit(0);
        }
    }
    exit(1);
}
