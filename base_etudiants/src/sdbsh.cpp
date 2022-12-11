#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



int main(int argc, char *argv[])
{
	// L'adresse IP du serveur récupéré à partir des arguments du programme.
	const std::string server_ip = argv[1];
	
	// Création d'un socket client
	int sock = checked(socket(AF_INET, SOCK_STREAM, 0));
	
	// Configuration adresse du serveur
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8080);
	
	// Connexion socket client au serveur
	checked(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)));
		
	char buffer[1024];
	int longueur,i,ret;
	
	//Permet de lire les entrées de l'utilisateur et
	//envoie les différentes requêtes au serveur
	
	while (fgets(buffer, 1024, stdin) != NULL) {
     longueur = strlen(buffer) + 1;
     
     // Envoi de la requête au serveur
     
     printf("Envoi...\n");
     longueur = htonl(longueur);
     checked_wr(write(sock, buffer, strlen(buffer) + 1));
     
     // Réponse du serveur est lue dans une boucle
     // Les données du socket sont lus jusqu'à ce qu'un certain nombre
     // d'octets soit lu. Cela permet de s'assurer que la réponse complète 
     //du serveur est lue avant de l'afficher à l'utilisateur.
     
     i = 0;
     while(i<longueur)  {
		 ret = read(sock, buffer, longueur - i)
		 if (ret <= 0) {
           if (ret < 0)
              perror("read");
           else
              printf("Déconnexion du serveur.\n");
           return 1;
        }
        i += ret;
     }
     printf("Recu : %s\n", buffer)
		 
		 }
		 
	// Fermeture du socket client
  close(sock);
  return 0;
  }
     
     	
	// Pour chaque requête valide entrée, on demande à l'utilisateur de spécifier ce qu'il veut
	
	
	// SELECT
	// INSERT
	// UPDATE
	// DELETE



