#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/socket.h>

#define MAXADDRLEN	256
#define BUFLEN		128
#define MAXSLEEP 128


int
connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen)
{
    int nsec;

    /*
     * Try to connect with exponential backoff.
     */
    for (nsec = 1; nsec <= MAXSLEEP; nsec <<= 1) {
        if (connect(sockfd, addr, alen) == 0) {
            /*
             * Connection accepted.
             */
            return(0);
        }

        /*
         * Delay before trying again.
         */
        if (nsec <= MAXSLEEP/2)
            sleep(nsec);
    }
    return(-1);
}
void
print_uptime(int sockfd)
{
    int		n;
    void*	buf[BUFLEN];
    int     output_fd;
            output_fd = open("/home/lilelr/CLionProjects/acumulation/NetworkIPCServer/happy_new_year",O_WRONLY|O_CREAT|O_APPEND,777);
    while ((n = recv(sockfd, buf, BUFLEN, 0)) > 0){
        printf("%d\n",n);
        write(output_fd, buf, n);

    }
    close(output_fd);
    if (n < 0)
        printf("recv error");
}

int
main(int argc, char *argv[])
{
    struct addrinfo	*ailist, *aip;
    struct addrinfo	hint;
    int				sockfd, err;

    if (argc != 2)
        printf("usage: ruptime hostname");
    hint.ai_flags = 0;
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if ((err = getaddrinfo(argv[1], "nfs", &hint, &ailist)) != 0)
        printf("getaddrinfo error: %s", gai_strerror(err));
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0)
            err = errno;
        if (connect_retry(sockfd, aip->ai_addr, aip->ai_addrlen) < 0) {
            err = errno;
        } else {
            print_uptime(sockfd);
            exit(0);
        }
    }
    fprintf(stderr, "can't connect to %s: %s\n", argv[1],
            strerror(err));
    exit(1);
}
