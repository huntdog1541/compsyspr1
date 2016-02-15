/*
*  A small client example
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char * msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char ** argv)
{
  int sockfd, portnumber, n;
  struct sockaddr_in server_addr;
  struct hostent * server;
  char buffer[256];
  if(argc < 3)
  {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }
  portnumber = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
      error("ERROR: error opening socket\n");
  }
  server = gethostbyname(argv[1]);
  if(server == NULL)
  {
    fprintf(stderr, "ERROR: no such host\n");
    exit(0);
  }
  bzero((char *) &server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
  server_addr.sin_port = htons(portnumber);
  if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    error("ERROR: error on connection\n");
  }
  printf("Please enter the message: ");
  bzero(buffer, 256);
  fgets(buffer, 255, stdin);
  n = write(sockfd, buffer, strlen(buffer));
  if(n < 0)
  {
    error("ERROR: error writing to socket\n");
  }
  bzero(buffer, 256);
  n = read(sockfd, buffer, 255);
  if(n < 0)
  {
    error("ERROR: error reading from socket\n");
  }
  printf("%s\n", buffer);
  return 0;
}
