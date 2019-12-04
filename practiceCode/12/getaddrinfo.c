/* getaddrinfo.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
int main(int argc, char * argv[])
{
struct addrinfo  hints, *res = NULL;
int rc;
char buf[256];
memset(&hints, 0, sizeof(hints)); 
/*设置addrinfo 结构体中各参数 */
hints.ai_flags = AI_CANONNAME;
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_DGRAM;
hints.ai_protocol = IPPROTO_UDP;
/*调用getaddinfo 函数*/
if(argc<2)
sprintf(buf,"localhost");
else
sprintf(buf,"%s",argv[1]);
rc = getaddrinfo(buf, NULL, &hints, &res);
if (rc != 0)
{
perror("getaddrinfo");
exit(1);
}
else
{
printf("Host name is %s\n", res->ai_canonname );
}

struct addrinfo *cur;
struct sockaddr_in *addr;
char ipbuf[16];
for (cur = res ; cur != NULL; cur = cur->ai_next) 
{
addr = (struct sockaddr_in *)cur->ai_addr;
inet_ntop(AF_INET,&addr->sin_addr, ipbuf, 16);
printf("%s\n", ipbuf); }


exit(0);
}

