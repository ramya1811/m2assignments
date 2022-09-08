#include<udp.h>
//default constructor
TcpClient::TcpClient()
{
	tport=3030;
	tipaddr="0.0.0.0";
}
//parameterized constructor
TcpClient::TcpClient(int portno,string ipaddress)
{
	tport=portno;
	tipaddr=ipaddress;
}
//to create tcp socket
void TcpClient::tcpcreatesocket(int tport,string tipaddr)
{
	tcpsocket =socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(tcpsocket < 0)
	{
		perror("socket() error");
		exit(EXIT_FAILURE);
	}
	tcpserveraddress.sin_family = AF_INET;
	tcpserveraddress.sin_port = htons(tport);
	tcpserveraddress.sin_addr.s_addr = inet_addr((const char*)tipaddr.c_str());
}
//to connect socket to the address
void TcpClient::tcpconnect()
{
	if(connect(tcpsocket,(struct sockaddr*)&tcpserveraddress,sizeof(tcpserveraddress))<0)
	{
		perror("connect");
		exit(1);
	}
}
//to send invite message to user agent server
void TcpClient::sendinvitemsgtoserver(string invitemsg)
{
		memset(tinvite_msg,'\0',sizeof(tinvite_msg));
		strcpy(tinvite_msg,(const char*)invitemsg.c_str());
		if(write(tcpsocket, tinvite_msg,SIZE)<0)
		{
			perror("write() error");
			exit(EXIT_FAILURE);
		}
}
//to receive response from user agent server and establish the connection
void TcpClient::sendmsgtotcpserver()
{
	while(1)
	{
		//to read responses and messages from user agent
		sleep(1);
		memset(tserver_msg,'\0',sizeof(tserver_msg));
		if(read(tcpsocket,tserver_msg,SIZE)<0)
		{
			perror("read() error");
			exit(EXIT_FAILURE);
		}
		//to send response to user agent
		if(strcmp(tserver_msg,"180 RINGING\n200 OK")==0)
		{
			cout<<"--------RESPONSE FROM USER AGENT SERVER TO USER AGENT CLIENT---------"<<endl;
			cout<<tserver_msg<<endl;
			cout<<"-------------------SESSION ESTABLISHED--------------------"<<endl;
		}
		else if(strcmp(tserver_msg,"200 OK")==0)
		{
			cout<<tserver_msg<<endl;
			break;
			exit(EXIT_SUCCESS);
		}
		else
		{
			sleep(1);
			cout<<"The message received from USER AGENT SERVER is:"<<endl;
			cout<<tserver_msg<<endl;
		}
		//to send ack response
		if(strcmp(tserver_msg,"180 RINGING\n200 OK")==0)
		{
			memset(tclient_msg,'\0',sizeof(tclient_msg));
			strcpy(tclient_msg,"ACK");
			if(write(tcpsocket, tclient_msg,SIZE)<0)
			{
				perror("write() error");
				exit(EXIT_FAILURE);
			}
		}
		//to terminate the session
		else if(strcmp(tserver_msg,"BYE")==0)
		{
			memset(tclient_msg,'\0',sizeof(tclient_msg));
			strcpy(tclient_msg,"200 OK");
			if(write(tcpsocket,tclient_msg,SIZE)<0)
			{
				perror("write() error");
				exit(EXIT_FAILURE);
			}
		}
		//to send message to user agent server
		else
		{
			sleep(1);
			cout<<"Enter the message to send to USER AGENT SERVER:"<<endl;
			string cmsg;
			getline(cin,cmsg);
			memset(tclient_msg,'\0',sizeof(tclient_msg));
			strcpy(tclient_msg,(const char*)cmsg.c_str());
			if(write(tcpsocket, tclient_msg,SIZE)<0)
			{
				perror("write() error");
				exit(EXIT_FAILURE);
			}
		}
		if(strcmp(tclient_msg,"200 OK")==0)
		{
			break;
		}
		
	}
	cout<<"-----------------------SESSION TERMINATED--------------------"<<endl;
	exit(EXIT_SUCCESS);
}
//to close the tcp socket
void TcpClient::tcpclosesocket()
{
	cout<<"close socket"<<endl;
	close(tcpsocket);
}
//destructor
TcpClient::~TcpClient()
{
}
