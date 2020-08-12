// http://github.com/iagor0ger

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER 1024

int main(int argc, char *argv[])
{
   struct sockaddr_in d;
   int msocket, con, rec, port;
   char buff[BUFFER];

   if ((msocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
   {
      perror("socket()");
      exit(1);
   }

   if (argc < 3)
   {
      printf("Usage:\n"            \
         "\t $ %s <host> <port>\n"   \
         "Ex:\t $ %s 127.0.0.1 22\n", argv[0], argv[0]);
      exit(1);
   }

   port = atoi(argv[2]);

   d.sin_family = AF_INET;
   d.sin_port = htons(port);
   d.sin_addr.s_addr = inet_addr(argv[1]);
   memset(&(d.sin_zero), 0x0, sizeof(d.sin_zero));

   if ((con = connect(msocket, (struct sockaddr *)&d, sizeof(d))) == -1)
   {
      perror("connect()");
      exit(1);
   }

   if ((rec = recv(msocket, buff, BUFFER, 0)) == -1)
   {
      perror("recv()");
      exit(1);
   }
   else
   {
      printf("Service: %s", buff);
      exit(1);
   }

   return 0;
}
