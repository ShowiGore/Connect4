#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <pthread.h>

char ibuffer[2][2000];
int i = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* recvConnectionTd(void *arg /*el socket*/)
{
    int newSocket = *((int *)arg);
    int buffindex = i % 2;

    recv(newSocket , ibuffer, 2000 , 0);

    pthread_mutex_lock(&lock);

    printf("Hola del thread\n");
    /*guardar datos de la conexion entrante*/

    pthread_mutex_unlock(&lock);

    //dependiendo del estado del otro segmento, wait, o enviar datos 

}

int main()
{
    pthread_t threads[2];

    int serverSocket, newSocket; 
    struct sockaddr_in address;
    struct sockaddr_storage serverStorage; 
    socklen_t addr_size;


    serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
   
    if(serverSocket == -1)
    {
        printf("Fallo al crear el socket");
    }
    else
    {
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = INADDR_ANY; 
        address.sin_port = htons(6466); 

        memset(address.sin_zero, '\0', sizeof address.sin_zero);
 
        if (bind(serverSocket, (struct sockaddr *)&address,sizeof(address))<0) 
        { 
            perror("bind failed"); 
        }
        
        if(listen(serverSocket,50)==0)
            printf("Listening\n");
        else
            printf("Error\n");
     
       
        while(1)        
        {
            
            addr_size = sizeof(serverStorage);
            printf("%d\n", i);
            newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
                       // accept(sockfd, (SA*)&cli, &len);
            
            printf("Server Listening...\n");

            //printf("Wait?\n"); 

            if( pthread_create(&threads[i++], NULL, recvConnectionTd, &newSocket) != 0 )
            {
                printf("Failed to create thread\n");
            }

        }
    }
        
}
    











