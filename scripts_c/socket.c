#include <stdio.h>
#include <netdb.h>

main()
{
	int meusocket;
	int conecta;

	struct sockaddr_in alvo;

	meusocket = socket (AF_INET, SOCK_STREAM, 0);
	alvo.sin_family = AF_INET;
	alvo.sin_port = htons (1337);
	alvo.sin_addr.s_addr = inet_addr ("172.16.1.5");

	conecta = connect(meusocket, (struct sockaddr *)&alvo, sizeof alvo);	

	if(conecta == 0)
	{
		printf("PORTA ABERTA \n");
		close(meusocket);
		close(conecta);
	}
	else {
		printf("PORTA FECHADA \n");
		}
}
