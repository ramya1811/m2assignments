#include<udp.h>
TcpServer::TcpServer()
{
	tport=3030;
	tipaddr="0.0.0.0";
}
TcpServer::TcpServer(int portno,string ipaddress)
{
	tport=portno;
	tipaddr=ipaddress;
}
void TcpServer::tcpcreatesocket(int tport,string argv)
{
	tcpsocket=socket(AF_INET,SOCK_STREAM,0);
	if(tcpsocket<0)
	{
		perror("tcpsocket");
	        exit(EXIT_FAILURE);
	}
	memset(&tcpserveraddress,0,sizeof(tcpserveraddress));
	tcpserveraddress.sin_family=AF_INET;
	tcpserveraddress.sin_port=htons(tport);
	tcpserveraddress.sin_addr.s_addr=inet_addr("127.0.0.1");
	cout<<"tcp server socket created"<<endl;
}
void TcpServer::tcpbind()
{
	tbind = bind(tcpsocket,(struct sockaddr *)&tcpserveraddress, sizeof(tcpserveraddress));
	if(tbind < 0)
	{
		perror("bind() error");
		exit(EXIT_FAILURE);
	}
	cout<<"Server socket successfully binded"<<endl;
}
void TcpServer::listening()
{
	if(listen(tcpsocket,5) !=0 )
        {
	        perror("listen() error");
	        exit(EXIT_FAILURE);
	}
	listen(tcpsocket,5);
	cout<<"server listening"<<endl;
}
void TcpServer::tcpaccept()
{
	sockacc=accept(tcpsocket,(struct sockaddr*)&tcpclientaddress,(socklen_t*)&tclient_addr_len);
	if(sockacc<0)
	{
		perror("accept() error");
		exit(EXIT_FAILURE);
	}
}
void TcpServer::receivemsgfromtcpclient()
{
	memset(tserver_msg,'\0',sizeof(tserver_msg));
	if(read(sockacc,tserver_msg,sizeof(tserver_msg))<0)
	{
		perror("read() error");
		exit(EXIT_FAILURE);
	}
	cout<<"Message received from tcp client is:"<<tserver_msg<<endl;
}
void TcpServer::sendmsgtotcpclient()
{
	memset(tclient_msg,'\0',sizeof(tclient_msg));
	strcpy(tclient_msg,tserver_msg);
	if(write(sockacc, tclient_msg, strlen(tclient_msg))<0)
	{
		perror("write() error");
		exit(EXIT_FAILURE);
	}
}
void TcpServer::tcpclosesocket()
{
	close(tcpsocket);
}
TcpServer::~TcpServer()
{
}
