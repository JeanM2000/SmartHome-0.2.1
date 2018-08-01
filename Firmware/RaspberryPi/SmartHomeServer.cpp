#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int arr[2][4];

int main()
{
  int col=0;
  int argc=3;
  int portno=7777;
    printf("Starting Listener\n");
     int sockfd, newsockfd;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");

        int enable = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
            error("setsockopt(SO_REUSEADDR) failed");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");

     printf("about to listen\n");
     listen(sockfd,5);
     printf("finished listening\n");
     clilen = sizeof(cli_addr);
     printf("About to accept\n");

     for(int i=0; i<100;){
         newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);

         if (newsockfd < 0)
             error("ERROR on accept");
         bzero(buffer,256);
         n = read(newsockfd,buffer,255);
         if (n < 0) error("ERROR reading from socket");

         printf("Here is the message: %s\n",buffer);
int buff[10];
         for (int i = 0; i < 10; i++) {
           buff[i] = buffer[i] - 48;
         }

         for (int i = 0; i < 10; i++) {
           cout << buffer[i] << endl;
         }
              int row=0;
              int adr=0;
              int sen=0;
              int typ=0;
              int dat=0;

                adr = buff[0]*100 + buff[1]*10 + buff[2];
                sen = buff[3]*100 + buff[4]*10 + buff[5];
                typ = buff[6];
                dat = buff[7]*100 + buff[8]+10 + buff[9];
                row = adr + sen;

                  cout << adr << endl;
                  cout << sen << endl;
                  cout << typ << endl;
                  cout << row << endl;

                arr[0][0] = adr;
                arr[0][1] = sen;
                arr[0][2] = typ;
                arr[0][3] = dat;

              for(int a=0; a<2; a++){
                for(int i=0; i<4; i++){
                  cout << arr[a][i] << "\t";
                }
                cout << endl;
              }

         n = write(newsockfd,"I got your message",18);
         if (n < 0) error("ERROR writing to socket");
         close(newsockfd);
     }
     close(sockfd);
     return 0;
}
