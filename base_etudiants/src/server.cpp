#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

const int PORT = 28772;

int main(void) {
	
	// Permet de définir un gestionnaire de signaux pour SIGPIPE,
	// ce qui évite une fermeture abrupte du programme à la réception
	// du signal
	signal(SIGPIPE, SIG_IGN);
	
	int serverfd = checked(socket(AF_INET, SOCK_STREAM, 0));
	
	int opt = 1;
	
	//Réutilisation de l'adresse/port
	setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	
	// Configuration adresse du serveur
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	// lier le socket créé précédemment à l'adresse IP et au port spécifiés dans la structure addresse
	checked(bind(serverfd, (struct sockaddr *)&address, sizeof(address)));
	
	// Socket en mode d'écoute, ce qui permet à d'autres sockets de se connecter à celui-ci
	checked(listen(serverfd, 3));
	
	
	// Calcule la taille de la structure address en utilisant la fonction sizeof() et stocke le résultat dans la variable addrlen
	size_t addrlen = sizeof(address);
	
	
	//Accepte une connexion entrante sur le socket en mode d'écoute et crée un nouveau socket 
    //pour cette connexion
	int new_socket = checked(accept(serverfd, (struct sockaddr *)&address, (socklen_t *)&addrlen));
	
	char buffer[1024];
	
	 //Déclare une variable entière appelée lu, qui sera utilisée
	 //pour stocker le nombre de caractères lus par le socket à chaque itération 
	 //de la boucle
  
	int lu;
	
	while ((lu = read(new_socket, buffer, 1024)) > 0) {
		
		// Ecris les données lues précédemment sur le socket new_socket
		checked_wr(write(new_socket, buffer, lu));
	
	}
	
	//Ferme le socket en mode d'écoute initialement créé
	close(serverfd);
	close(new_socket);
	
	return 0;
}
