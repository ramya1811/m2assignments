#pragma once
#include <iostream>
#include <string>
#include<errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include <netinet/in.h>
#include <cstring>
#include<arpa/inet.h>
#include<bits/stdc++.h>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

#define MYPORT 3030
#define SIZE 1024
#define BSIZE 1024
class UdpClient
{
	private:
		int sd;
		int uport;
		string uipaddr;
		struct sockaddr_in serveraddress,clientaddress;
		char server_msg[SIZE];
		char client_msg[SIZE];
		size_t server_addr_len=sizeof(serveraddress);
		size_t client_addr_len=sizeof(clientaddress);
		socklen_t len;
	public:
		UdpClient();
		UdpClient(int,string);
		void createsocket(int,string);
		void sendmsgtoudpserver();
		void receivemsgfromudpserver();
		void closesocket();
		~UdpClient();
};
class UdpServer
{
	private:
		int sd,ret;
		int uport;
		string uipaddr;
		struct sockaddr_in serveraddress,clientaddress;
		char server_msg[SIZE];
		char client_msg[SIZE];
		size_t server_addr_len=sizeof(serveraddress);
		size_t client_addr_len=sizeof(clientaddress);
		socklen_t len;
	public:
		UdpServer();
		UdpServer(int,string);
		void createsocket(int,string);
		void binding();
		void receivemsgfromudpclient();
		void sendmsgtoudpclient();
		void closesocket();
		~UdpServer();

};
class TcpClient
{
	private:
		int tcpsocket;
		int tport;
		string tipaddr;
		struct sockaddr_in tcpserveraddress,tcpclientaddress;
		char tserver_msg[SIZE];
		char tclient_msg[SIZE];
		size_t tserver_addr_len=sizeof(tcpserveraddress);
		size_t tclient_addr_len=sizeof(tcpclientaddress);
	public:
		TcpClient();
		TcpClient(int,string);
		void tcpcreatesocket(int,string);
		void tcpconnect();
		void receivemsgfromtcpserver();
		void sendmsgtotcpserver();
		void tcpclosesocket();
		~TcpClient();

};
class TcpServer
{
	private:
		int tcpsocket,tbind,sockacc;
		int tport;
		string tipaddr;
		struct sockaddr_in tcpserveraddress,tcpclientaddress;
		char tserver_msg[SIZE];
		char tclient_msg[SIZE];
		size_t tserver_addr_len=sizeof(tcpserveraddress);
		size_t tclient_addr_len=sizeof(tcpclientaddress);

	public:
		TcpServer();
		TcpServer(int,string);
		void tcpcreatesocket(int,string);
		void tcpbind();
		void listening();
		void tcpaccept();
		void receivemsgfromtcpclient();
		void sendmsgtotcpclient();
		void tcpclosesocket();
		~TcpServer();
	
};
/*	private:
		sem_t x,y;
		pthread_t tid;
		int tcpsocket,tbind,sockacc;
		int sd,ret;
		struct sockaddr_in serveraddress,clientaddress,tcpserveraddress;
		socklen_t len;
		char server_msg[SIZE];
		char client_msg[SIZE];
		char buf[BSIZE];
		size_t server_addr_len=sizeof(serveraddress);
		size_t client_addr_len=sizeof(clientaddress);
	public:
		Udp();
		void createsocket();
		void createtcpsocket();
		void tcpproxysocket();
		void tcpconnect();
		void accepttcp();
		void createsocketforclient(int);
		void binding();
		void tcpbind();
		void listening();
		void receivemsgfromclient(char *);
		void sendmsgtoclient(char *);
		void sendmsgtotcpclient(char *);
		void sendmessagetoserver(char*);
		void receivemessagefromserver(char *);
		void ringingresponse();
		void ringing(char *);
		void acceptringing();
		void requestfromproxy(char*);
		void okresponse();
		void ackrequest();
		~Udp();
};*/
