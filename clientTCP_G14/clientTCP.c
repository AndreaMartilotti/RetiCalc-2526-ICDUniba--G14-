/*
 * clientTCP.c
 *
 *  Created on: 16 dic 2025
 *      Author: ASUS
 */


#include <stdio.h>
#include <winsock.h>
#include <string.h>

#define porta 27015
#define LEN_MAX 40


typedef struct _MSG {
	int valore;
	char testo[LEN_MAX];
} MSG;

int main() {

	int ClientSocket;
	struct sockaddr_in server_address;
	struct hostent *hp;
	MSG messaggio;


// creazione socket client

	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket < 0) {
		perror( "Errore creazione socket client\n" );
		return -1;
	}


// binding

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	server_address.sin_port = htons(porta);


	// (host aliasing)

	hp = gethostbyname("localhost"); // indirizzo 27015
	if (hp < 0) {
			perror( "Errore localhost\n" );
			return -1;
		}


//connessione

	if (connect(ClientSocket, (struct sockaddr *)&server_address, sizeof(server_address)) <0) {
		perror("Errore connessione");
		return -1;
	}

	printf("Connesso al server\n");



// messaggio

	messaggio.valore = 10;
	strcpy(messaggio.testo, "prova mess");
	if (send(ClientSocket, &messaggio, sizeof(messaggio)) <0) {
		perror("Errore send");
		return -1;
	}





	return 0;
}
