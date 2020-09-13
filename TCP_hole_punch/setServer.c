#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>

char ibuffer[2000];

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* recvConnectionTd(void *arg /*el socket*/)
{
    int newSocket = *((int *)arg);
    
    recv(newSocket , ibuffer, 2000 , 0);

    pthread_mutex_lock(&lock);

    /*guardar datos de la conexion entrante*/

    pthread_mutex_unlock(&lock);

    //dependiendo del estado del otro segmento, wait, o enviar datos 

}

int main()
{
    pthread_t threads[2];












}