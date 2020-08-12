 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
 
 void scanner(int port, char host[]);
 
 int main(int argc, char **argv) {
	 char host[100];
	 char *p;
	 int ports[10];
	 int i = 0;
	 int var;
	 char tok[] = " ,";
	 
	 if (argc < 2) {
		 fprintf(stderr,"[+]usage: %s <hostname> <port,port,port...>\n", argv[0]);
		 exit(0);
	 }
	 
	 p = strtok(argv[2], tok);
	 strcpy(host, argv[1]);
	 while(p != NULL) {
		 sscanf(p, "%d", &var);
		 ports[i++] = var;
		 p = strtok(NULL, tok);
	 }
	 
	 for(i=0; i<(sizeof(ports)/sizeof(ports[0])); i++) {
		 fprintf(stdout, "\n[+]Testing port: %d\n", ports[i]);
		 scanner(ports[i], host);
	 }
	 return 0;
 }
 
 void scanner(int port, char host[]) {
	 
	 int sock, n;
	 struct hostent *server;
	 struct sockaddr_in serv_addr;
	 
	 char buffer[4096];
	 
	 server = gethostbyname(host);
	 
	 sock = socket(AF_INET, SOCK_STREAM, 0);
	 /* Edit the params of socket to scan UDP ports,
	  * should be pretty straight forward I suppose.
	  */
	 
	 if(sock < 0) {
		 fprintf(stderr, "[-]Error creating socket");
		 return;
	 }
	 
	 bzero((char *) &serv_addr, sizeof(serv_addr));
	 serv_addr.sin_family = AF_INET;
	 // AF_UNIX for Unix style socket
	 
	 bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	 serv_addr.sin_port = htons(port);
	 
	 n = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	 sleep(2);
	 if(n < 0) {
		 fprintf(stderr, "[-]Error Connecting to port\n");
		 return;
	 }
	 
	 memset(buffer, 0, sizeof(buffer));
	 strcpy(buffer, "garbage\r\n");
	 
	 n = write(sock, buffer, strlen(buffer));
	 if(n < 0) {
		 fprintf(stderr, "[-]Error writing (Port closed maybe?!)\n");
		 return;
	 }
	 
	 bzero(buffer, 4096);
	 n = read(sock, buffer, 4096);
	 if(n < 0) {
		 fprintf(stderr, "[-]Error reading (Port closed maybe?!)\n");
		 return;
	 }
	 
	 fprintf(stdout,"[*]%s\n", buffer);
	 close(sock);
	 
 }
