#pragma once
#include <iostream>
#include <string.h>
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
#include<mutex>
#include<sstream>
#include<semaphore.h>
#include<fcntl.h>
#include<fstream>
using namespace std;
#define MYPORT 3030
#define SIZE 2048
#define BSIZE 1024
class UdpClient
{
	private:
		//date members
		int sd;
		int uport;
		string uipaddr;
		struct sockaddr_in serveraddress,clientaddress;
		char server_msg[SIZE];
		char client_msg[SIZE];
		char invite_msg[SIZE];
		size_t server_addr_len=sizeof(serveraddress);
		size_t client_addr_len=sizeof(clientaddress);
		socklen_t len;
	public:
		//default constructor
		UdpClient();
		//parameterized constructor
		UdpClient(int,string);
		//function declaration 
		//To create udp socket
		void createsocket(int,string);
		//To send invite request to proxy server
		void sendinvitemsg(string);
		//to receive response
		void receiveresponsefromudpserver();
		//To close udp socket
		void closesocket();
		//destructor
		~UdpClient();
};
class UdpServer
{
	private:
		//data members
		int sd,ret;
		int uport;
		string uipaddr;
		struct sockaddr_in serveraddress,clientaddress;
		char server_msg[SIZE];
		char client_msg[SIZE];
		char invite_msg[SIZE];
		size_t server_addr_len=sizeof(serveraddress);
		size_t client_addr_len=sizeof(clientaddress);
		socklen_t len;
	public:
		//constructor
		UdpServer();
		//parameterized constructor 
		UdpServer(int,string);
		//To create udp socket
		void createsocket(int,string);
		//To bind socket to the server address
		void binding();
		//to receive invite request from user agent client
		void receiveinvitemsg();
		//to send responses
		void sendresponsetoudpclient();
		//to close udp socket
		void closesocket();
		//destructor
		~UdpServer();

};
class TcpClient
{
	private:
		//data members
		int tcpsocket;
		int tport;
		string tipaddr;
		struct sockaddr_in tcpserveraddress,tcpclientaddress;
		char tserver_msg[SIZE];
		char tclient_msg[SIZE];
		char tinvite_msg[SIZE];
		size_t tserver_addr_len=sizeof(tcpserveraddress);
		size_t tclient_addr_len=sizeof(tcpclientaddress);
	public:
		//default constructor
		TcpClient();
		//parameterized constructor
		TcpClient(int,string);
		//to create tcp socket
		void tcpcreatesocket(int,string);
		//to connect
		void tcpconnect();
		//to send invite message to user agent server
		void sendinvitemsgtoserver(string);
		//to receive responses and to establish connection
		void sendmsgtotcpserver();
		//to close tcp socket
		void tcpclosesocket();
		//destructor
		~TcpClient();

};
class TcpServer
{
	private:
		//data members
		int tcpsocket,tbind,sockacc;
		int tport;
		string tipaddr;
		struct sockaddr_in tcpserveraddress,tcpclientaddress;
		char tserver_msg[SIZE];
		char tclient_msg[SIZE];
		char tinvite_msg[SIZE];
		size_t tserver_addr_len=sizeof(tcpserveraddress);
		size_t tclient_addr_len=sizeof(tcpclientaddress);

	public:
		//default constructor
		TcpServer();
		//parameterized constructor
		TcpServer(int,string);
		//to create tcp socket
		void tcpcreatesocket(int,string);
		//to bind socket to the address
		void tcpbind();
		//to put server socket to wait for client
		void listening();
		//to extract the first connection in queue
		void tcpaccept();
		//to receive invite message from proxy server
		void receiveinvitemsg();
		//to send responses and to establish connection
		void sendmsgtotcpclient();
		//to close the tcp socket
		void tcpclosesocket();
		//destructor
		~TcpServer();
	
};
