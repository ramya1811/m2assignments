#include<udp.h>
TcpClient::TcpClient()
{
	tport=3030;
	tipaddr="0.0.0.0";
}
TcpClient::TcpClient(int portno,string ipaddress)
{
	tport=portno;
	tipaddr=ipaddress;
}
void TcpClient::tcpcreatesocket(int tport,string tipaddr)
{
	tcpsocket =socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(tcpsocket < 0)
	{
		perror("socket() error");
		exit(EXIT_FAILURE);
	}
	cout<<"tcp proxy Socket is created"<<endl;
	tcpserveraddress.sin_family = AF_INET;
	tcpserveraddress.sin_port = htons(tport);
	tcpserveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
}
void TcpClient::tcpconnect()
{
	if(connect(tcpsocket,(struct sockaddr*)&tcpserveraddress,sizeof(tcpserveraddress))<0)
	{
		perror("connect");
		exit(1);
	}
	cout<<"Connected to tcp"<<endl;
}
void TcpClient::sendmsgtotcpserver()
{
	string cmsg;
	getline(cin,cmsg);
	memset(tclient_msg,'\0',sizeof(tclient_msg));
	strcpy(tclient_msg,(const char*)cmsg.c_str());
	if(write(tcpsocket, tclient_msg, strlen(tclient_msg))<0)
	{
		perror("write() error");
		exit(EXIT_FAILURE);
	}
}
void TcpClient::receivemsgfromtcpserver()
{
	memset(tserver_msg,'\0',sizeof(tserver_msg));
	if(read(tcpsocket,tserver_msg,sizeof(tserver_msg))<0)
	{
		perror("read() error");
		exit(EXIT_FAILURE);
	}
	cout<<"message sent to tcp server is:"<<tserver_msg<<endl;
}
void TcpClient::tcpclosesocket()
{
	close(tcpsocket);
}
TcpClient::~TcpClient()
{
}
