#include<stdio.h>
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

/*#define  CLI_HOST_ADDR  "157.230.41.161"
#define  CLI_UDP_PORT  7450 */

#define  CLI_HOST_ADDR  "37.111.228.69"
#define  CLI_UDP_PORT  8450 


int main(int argc,char* argv[])
{
	
  int pn=-1;
  if(argc>1)
    pn=atoi(argv[1]);
  
  int sfd;
  struct sockaddr_in ser_addr, cli_addr;
  const int MAXLEN=2048;
  char rec_buf[MAXLEN+1];

  bzero((char*)& cli_addr,sizeof( cli_addr));
   cli_addr.sin_family = AF_INET;
   cli_addr.sin_addr.s_addr = inet_addr(( argc<3) ?  CLI_HOST_ADDR : argv[2]);
   cli_addr.sin_port = htons((pn==-1) ?  CLI_UDP_PORT : pn);

  if( (sfd = socket(AF_INET,SOCK_DGRAM,0))<0)
    perror("socket fails");
  bzero((char*)&ser_addr,sizeof(ser_addr));

  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr.sin_port = htons(8450);

  if(bind(sfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr))<0)
    perror("can't bind");
  
   char sendline[2048],rline[2048+1];
  
  while(fgets(sendline,2048,stdin)!=NULL)
    {
   
      
      int m_len=strlen(sendline);
	struct sockaddr* sa =  (struct sockaddr * ) & cli_addr;
	/*if(sendto(sfd,sendline,m_len,0,(struct sockaddr * )& cli_addr,sizeof( cli_addr))==-1)
	  perror("send err");
*/
int dst_port =1;
	while(1)
	  {	  
       cli_addr.sin_port = htons(dst_port); 
	char port [5];	
       sprintf(port, "%d", dst_port);
		if(sendto(sfd,port,m_len,0,(struct sockaddr * )& cli_addr,sizeof( cli_addr))==-1){       
		perror("send err");
		}	   
	cout<<dst_port<<endl; 
       ++dst_port;
       if(dst_port == 64999) 
	break;  
      }
	  unsigned clilen=MAXLEN;
	int n = recvfrom(sfd,rline,100,0,(struct sockaddr*) &cli_addr, &clilen);
	if(n<0) perror("Err rec");
	rline[n]=0;
	cout<<rline<<endl;
	
	
   
    }

  
  close(sfd);
  return 0;
}











