#include<functions.h>
int Tcp_Server(char *argv[])
{
	TcpServer *ts=new TcpServer(atoi(argv[2]),argv[1]);
	//TcpServer ts;
	int tport=atoi(argv[2]);
	string tipaddr=argv[1];
	ts->tcpcreatesocket(tport,tipaddr);
	ts->tcpbind();
	ts->listening();
	while(true)
	{
		ts->tcpaccept();
		if(fork()==0)
		{
			while(1)
			{
				ts->receivemsgfromtcpclient();
				ts->sendmsgtotcpclient();
			}
		}
		ts->tcpclosesocket();
	}
	return 0;
}
int Tcp_Client(char *argv[])
{
	TcpClient *tc=new TcpClient(atoi(argv[2]),argv[1]);
	//TcpClient tc;
	int tport=atoi(argv[2]);
	string tipaddr=argv[1];
	tc->tcpcreatesocket(tport,tipaddr);
	tc->tcpconnect();
	while(1)
	{
		tc->sendmsgtotcpserver();
		tc->receivemsgfromtcpserver();
	}
	tc->tcpclosesocket();
	return 0;
}
int Udp_Client(char *argv[])
{
	UdpClient *uc=new UdpClient(atoi(argv[2]),argv[1]);
	//UdpClient uc;
	int port=atoi(argv[2]);
	uc->createsocket(port,argv[1]);
	while(1)
	{
		uc->sendmsgtoudpserver();
		uc->receivemsgfromudpserver();
	}
	uc->closesocket();
	return 0;
}
int Udp_Server(char *argv[])
{
	UdpServer *us=new UdpServer(atoi(argv[2]),argv[1]);
	//UdpServer us;
	int port=atoi(argv[2]);
	string ipaddr=argv[1];
	us->createsocket(port,ipaddr);
	us->binding();
	while(1)
	{
		if(fork()==0)
		{
			us->receivemsgfromudpclient();
			us->sendmsgtoudpclient();
		}
		else
		{
			us->closesocket();
			wait(0);
		}
	}
	us->closesocket();
	return 0;
}

	
