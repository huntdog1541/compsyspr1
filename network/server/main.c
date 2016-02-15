/*
*  A small server program to execute
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char * msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char ** argv)
{
  int sockfd, nwsockfd portnumber, clilen;
  char buffer[256];
  struct sockaddr_in server_addr, cli_addr;
  int n;
  if(argc < 2) {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
    error("ERROR, opening socket\n");
  }
  bzero((char*) &server_addr, sizeof(server_addr));
  portnumber = atoi(argv[1]);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(portnumber);
  if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
  {
    error("ERROR: error on binding\n");
  }
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  nwsockfd = accept(sockfd, (struct sockaddr * ) &cli_addr, &clilen);
  if(nwsockfd < 0)
  {
    error("ERROR: error on accept\n");
  }
  bzero(buffer);
  n = read(nwsockfd, buffer, 255);
  if(n < 0) error("ERROR: error reading from socket\n");
  printf("Message: %s\n");
  n = write(nwsockfd, "I got your message", 18);
  if(n < 0) error("ERROR: error writing to socket\n");
  return 0;
}
