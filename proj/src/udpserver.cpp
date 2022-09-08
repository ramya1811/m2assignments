#include<udp.h>
//default constructor
UdpServer::UdpServer()
{
	uport=3031;
	uipaddr="0.0.0.0";
}
//parameterized constructor
UdpServer::UdpServer(int portno,string ipaddress)
{
	uport=portno;
	uipaddr=ipaddress;
}
//to create udp socket
void UdpServer::createsocket(int port,string ipaddr)
{
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0) {
		perror("socket");
		exit(1);
	}
        memset(&serveraddress,0,sizeof(serveraddress));
        serveraddress.sin_family=AF_INET;
        serveraddress.sin_port=htons(port);
        serveraddress.sin_addr.s_addr=inet_addr((const char*)ipaddr.c_str());
}
//to bind socket to server address
void UdpServer::binding()
{
	int ret=bind(sd,(struct sockaddr*)&serveraddress,sizeof(serveraddress));
	if ( ret < 0)
	{
		cout<<"Error in Bind"<<endl;
		perror("BIND");
		exit(1);
	}
}
//to receive invite message from user agent client
void UdpServer::receiveinvitemsg()
{
	memset(invite_msg,'\0',sizeof(invite_msg));
	if(recvfrom(sd,invite_msg,SIZE, 0,
		(struct sockaddr*)&clientaddress,(socklen_t*)&client_addr_len)<0)
	{
	        perror("recvfrom() error");
	        exit(EXIT_FAILURE);
	}
	char in[4][15]={"FROM:","IPADDRESS:","TO:","IPADDRESS:"};
	int i=0;
	cout<<"--------INVITE REQUEST FROM USER AGENT CLIENT TO PROXY SERVER--------"<<endl;
	char *token=strtok(invite_msg,"|");
	while(token)
	{
		cout<<in[i]<<token<<endl;
		token=strtok(NULL,"|");
		i++;
	}
}
//to send response to user agent client
void UdpServer::sendresponsetoudpclient()
{
	memset(server_msg,'\0',sizeof(server_msg));
	strcpy(server_msg,"100 TRYING");
	sleep(1);
	if(sendto(sd, server_msg, strlen(server_msg), 0,
		(struct sockaddr*)&clientaddress, client_addr_len)<0)
	{
		perror("sendto() error");
	        exit(EXIT_FAILURE);
	}
}
//to close udp socket
void UdpServer::closesocket()
{
	close(sd);
}
//destructor
UdpServer::~UdpServer()
{
}

