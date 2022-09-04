#include<udp.h>
UdpServer::UdpServer()
{
	uport=3031;
	uipaddr="0.0.0.0";
}
UdpServer::UdpServer(int portno,string ipaddress)
{
	uport=portno;
	uipaddr=ipaddress;
}
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
        serveraddress.sin_addr.s_addr=inet_addr("127.0.0.1");
        cout<<"udp server socket is created"<<endl;
}
void UdpServer::binding()
{
	int ret=bind(sd,(struct sockaddr*)&serveraddress,sizeof(serveraddress));
	if ( ret < 0)
	{
		cout<<"Error in Bind"<<endl;
		perror("BIND");
		exit(1);
	}
	cout<<"binded in udp"<<endl;
}
void UdpServer::receivemsgfromudpclient()
{
	memset(client_msg,'\0',sizeof(client_msg));
	if(recvfrom(sd,client_msg,sizeof(client_msg), 0,
		(struct sockaddr*)&clientaddress,(socklen_t*)&client_addr_len)<0)
	{
	        perror("recvfrom() error");
	        exit(EXIT_FAILURE);
	}
	cout<<"Message from the udp client:"<<client_msg<<endl;
}
void UdpServer::sendmsgtoudpclient()
{
	memset(server_msg,'\0',sizeof(server_msg));
	strcpy(server_msg,client_msg);
	sleep(1);
	if(sendto(sd, server_msg, strlen(server_msg), 0,
		(struct sockaddr*)&clientaddress, client_addr_len)<0)
	{
		perror("sendto() error");
	        exit(EXIT_FAILURE);
	}
}
void UdpServer::closesocket()
{
	close(sd);
}
UdpServer::~UdpServer()
{
}

