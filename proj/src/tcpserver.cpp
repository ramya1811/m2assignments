#include<udp.h>
//default constructor
TcpServer::TcpServer()
{
	tport=3030;
	tipaddr="0.0.0.0";
}
//parameterized constuctor
TcpServer::TcpServer(int portno,string ipaddress)
{
	tport=portno;
	tipaddr=ipaddress;
}
//to create tcp socket
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
	tcpserveraddress.sin_addr.s_addr=inet_addr((const char*)argv.c_str());
}
//to bind socket to the address
void TcpServer::tcpbind()
{
	tbind = bind(tcpsocket,(struct sockaddr *)&tcpserveraddress, sizeof(tcpserveraddress));
	if(tbind < 0)
	{
		perror("bind() error");
		exit(EXIT_FAILURE);
	}
}
//to connect to the user agent server
void TcpServer::listening()
{
	if(listen(tcpsocket,5) !=0 )
        {
	        perror("listen() error");
	        exit(EXIT_FAILURE);
	}
	listen(tcpsocket,5);
}
//to connect to the user agent server
void TcpServer::tcpaccept()
{
	sockacc=accept(tcpsocket,(struct sockaddr*)&tcpclientaddress,(socklen_t*)&tclient_addr_len);
	if(sockacc<0)
	{
		perror("accept() error");
		exit(EXIT_FAILURE);
	}
}
//to receive invite message from proxy server and send response to user agent client
void TcpServer::receiveinvitemsg()
{
	memset(tinvite_msg,'\0',sizeof(tinvite_msg));
	if(read(sockacc,tinvite_msg,sizeof(tinvite_msg))<0)
	{
		perror("read() error");
		exit(EXIT_FAILURE);
	}
	cout<<"-------------------------------------------------------"<<endl;
	cout<<"                WELCOME TO SIP APPLICATION             "<<endl;
	cout<<"-------------------------------------------------------"<<endl;
	cout<<"----------INVITE REQUEST FROM PROXY SERVER TO USER AGENT SERVER---------"<<endl;
	char in[4][15]={"FROM:","IPADDRESS:","TO:","IPADDRESS:"};
	int i=0;
	char *token=strtok(tinvite_msg,"|");
	while(token)
	{
		cout<<in[i]<<token<<endl;
		token=strtok(NULL,"|");
		i++;
	}
	memset(tclient_msg,'\0',sizeof(tclient_msg));
	strcpy(tclient_msg,"180 RINGING\n200 OK");
	if(write(sockacc, tclient_msg, strlen(tclient_msg))<0)
	{
		perror("write() error");
		exit(EXIT_FAILURE);
	}
}
//to send response to user agent client and establish the connection
void TcpServer::sendmsgtotcpclient()
{
	while(1)
	{
		//to read message and responses
		memset(tserver_msg,'\0',sizeof(tserver_msg));
		if(read(sockacc,tserver_msg,SIZE)<0)
		{
			perror("read() error");
			exit(EXIT_FAILURE);
		}
		if(strcmp(tserver_msg,"ACK")==0)
		{
			cout<<"-----------------------------RESPONSE FROM USER AGENT CLIENT------------------"<<endl;
			cout<<tserver_msg<<endl;
			cout<<"------------SESSION ESTABLISHED------------"<<endl;
		}
		else if(strcmp(tserver_msg,"200 OK")==0)
		{
			cout<<tserver_msg<<endl;
			break;
			exit(EXIT_SUCCESS);
		}
		else
		{
			cout<<"The message receive from USER AGENT CLIENT is:"<<endl;
			cout<<tserver_msg<<endl;
		}
		//to terminate the session
		if(strcmp(tserver_msg,"BYE")==0)
		{
			memset(tclient_msg,'\0',sizeof(tclient_msg));
			strcpy(tclient_msg,"200 OK");
			if(write(sockacc,tclient_msg,strlen(tclient_msg))<0)
			{
				perror("write() error");
				exit(EXIT_FAILURE);
			}
		}
		//to send message to user agent client
		else
		{
			cout<<"Enter the message to send to USER AGENT CLIENT:"<<endl;
			string smsg;
			getline(cin,smsg);
			memset(tclient_msg,'\0',sizeof(tclient_msg));
			strcpy(tclient_msg,(const char*)smsg.c_str());
			if(write(sockacc, tclient_msg, strlen(tclient_msg))<0)
			{
				perror("write() error");
				exit(EXIT_FAILURE);
			}
		}
		if(strcmp(tclient_msg,"200 OK")==0)
		{
			break;
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}
//to close tcp socket
void TcpServer::tcpclosesocket()
{
	close(tcpsocket);
}
//destructor
TcpServer::~TcpServer()
{
}
