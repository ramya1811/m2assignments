#include<udp.h>
#include<functions.h>
//default constructor
UdpClient::UdpClient()
{
	uport=3031;
	uipaddr="0.0.0.0";
}
//parameterized constructor
UdpClient::UdpClient(int portno,string ipaddress)
{
	uport=portno;
	uipaddr=ipaddress;
}
//to create udp socket
void UdpClient::createsocket(int port,string ipaddr)
{
	sd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sd < 0) {
       		perror("socket");
		exit(1);
	}
	memset(&serveraddress,'\0',sizeof(serveraddress));
	serveraddress.sin_family=AF_INET;
	serveraddress.sin_port=htons(port);
	serveraddress.sin_addr.s_addr=inet_addr((const char*)ipaddr.c_str());
}
//to send invite message to proxy server
void UdpClient::sendinvitemsg(string invitemsg)
{
       	memset(invite_msg,'\0',sizeof(invite_msg));
       	strcpy(invite_msg,(const char*)invitemsg.c_str());
       	if(sendto(sd, invite_msg, strlen(invite_msg), 0,
       	        (struct sockaddr*)&serveraddress,server_addr_len)<0)
       	{
       	         perror("sendto() error");
       	         exit(EXIT_FAILURE);
       	}
}
//to receive response from proxy server
void UdpClient::receiveresponsefromudpserver()
{
	sleep(1);
	memset(server_msg,'\0',sizeof(server_msg));
	if(recvfrom(sd, server_msg,SIZE, 0,
		(struct sockaddr*)&serveraddress,(socklen_t*)&server_addr_len)<0)
	{
	         perror("receivefrom() error");
	         exit(EXIT_FAILURE);
	}
	cout<<"-----------RESPONSE FROM PROXY SERVER TO USER AGENT CLIENT-----------"<<endl;
	cout<<server_msg<<endl;
}
//to close the socket
void UdpClient::closesocket()
{
	close(sd);
}
//destructor
UdpClient::~UdpClient()
{
}
