#include<udp.h>
#include<functions.h>
UdpClient::UdpClient()
{
	uport=3031;
	uipaddr="0.0.0.0";
}
UdpClient::UdpClient(int portno,string ipaddress)
{
	uport=portno;
	uipaddr=ipaddress;
}
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
	serveraddress.sin_addr.s_addr=inet_addr("127.0.0.1");
	cout<<"udp client socket is successfully created"<<endl;
}
void UdpClient::sendmsgtoudpserver()
{
       cout<<"Enter the request to send:"<<endl;
       memset(client_msg,'\0',sizeof(client_msg));
       string cmsg;
       getline(cin,cmsg);
       strcpy(client_msg,(const char*)cmsg.c_str());
       if(sendto(sd, client_msg, strlen(client_msg), 0,
               (struct sockaddr*)&serveraddress,server_addr_len)<0)
       {
                perror("sendto() error");
                exit(EXIT_FAILURE);
       }
	     //cout<<client_msg<<endl;
}
void UdpClient::receivemsgfromudpserver()
{
	sleep(1);
	memset(server_msg,'\0',sizeof(server_msg));
	if(recvfrom(sd, server_msg,SIZE, 0,
		(struct sockaddr*)&serveraddress,(socklen_t*)&server_addr_len)<0)
	{
	         perror("receivefrom() error");
	         exit(EXIT_FAILURE);
	}
	cout<<"The message receive from udpserver is:"<<server_msg<<endl;
}
void UdpClient::closesocket()
{
	close(sd);
}
UdpClient::~UdpClient()
{
}
