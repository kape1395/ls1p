#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netax25/axlib.h>
#include <netax25/ax25.h>
#include <netax25/axconfig.h>

/*
    http://www.spinics.net/lists/linux-hams/msg02958.html
    apt-get install libax25-dev 
*/
#include <stdio.h>
#include <sys/time.h>

void ax25_list_ports();


int ax25_init(int* sock, char* src_port, char* dst_call)
{
    int protocol = 0; /* Use default protocol */
    int sockfd;
    char* src_call;
    struct full_sockaddr_ax25 src_addr;
    struct full_sockaddr_ax25 dst_addr;
    unsigned src_addr_len;
    unsigned dst_addr_len;

    char buf[256];
    int buf_len = 256;
    int msg_len;
    struct timeval timeout;
    
    if (ax25_config_load_ports() == 0)
    {
        return -1001;
    }
    ax25_list_ports();

    if ((src_call = ax25_config_get_addr(src_port)) == NULL)
    {
        return -1002;
    }
    fprintf(stderr, "src_call=%s\n", src_call);
    fprintf(stderr, "dst_call=%s\n", dst_call);

    if ((src_addr_len = ax25_aton(src_call, &src_addr)) == -1)
    {
        return -1003;
    }
    if ((dst_addr_len = ax25_aton(dst_call, &dst_addr)) == -1)
    {
        return -1004;
    }
    
    if ((sockfd = socket(AF_AX25, SOCK_DGRAM, protocol)) == -1)
    {
        fprintf(stderr, "socket err=%d\n", errno);
        return errno;
    }
    if (bind(sockfd, (struct sockaddr *) &src_addr, src_addr_len) == -1)
    {
        fprintf(stderr, "bind err=%d\n", errno);
        return errno;
    }


    /*
     *  Try send something.
     */
    if (sendto(sockfd, "asd", 3, 0, (struct sockaddr *) &dst_addr, dst_addr_len) == -1)
    {
        fprintf(stderr, "sendto err=%d\n", errno);
        return errno;
    }


    /*
     *  Configure timeout for receive.
     */
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) != 0)
    {
        fprintf(stderr, "setsockopt err=%d\n", errno);
        return errno;
    }
    /*
     * Do receive.
     */
    fprintf(stderr, "recvfrom...\n");
    if ((msg_len = recvfrom(sockfd, &buf, buf_len, 0, (struct sockaddr *) &dst_addr, &dst_addr_len)) == -1)
    {
        fprintf(stderr, "recvfrom err=%d\n", errno);
        return errno;
    }
    fprintf(stderr, "recvfrom... done, msglen=%d\n", msg_len);

    *sock = sockfd;
    return 0;
}

void ax25_close()
{

}

void ax25_send()
{

}

void ax25_recv()
{

}

void ax25_list_ports()
{
    char* port = NULL;
    while ((port = ax25_config_get_next(port)) != NULL)
    {
        fprintf(stderr, "ax25_list_ports: port=%s name=%s\n", port, ax25_config_get_name(port));
    }
}
