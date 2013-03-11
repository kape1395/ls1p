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


int ax25_init(int* sock)
{
    int prot = 0; /* Use default protocol */
    int sockfd;
    
    if (ax25_config_load_ports() == 0)
    {
        return -1;
    }

    if ((sockfd = socket(AF_AX25, SOCK_DGRAM, prot)) == -1)
    {
        return errno;
    }

/*
    struct sockaddr
    int binderr = bind(sockfd, )
*/

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

