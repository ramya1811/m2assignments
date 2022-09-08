#include<functions.h>
#include<udp.h>
void *UA_Server(void *param)
{
	//locks the mutex object
	pthread_mutex_lock(&x);
	char **argv=(char**)param;
	//object creation
	TcpServer *ts=new TcpServer(atoi(argv[2]),argv[1]);
	int tport=atoi(argv[2]);
	string tipaddr=argv[1];
	//function call to create tcp socket
	ts->tcpcreatesocket(tport,tipaddr);
	//function call to tcp bind
	ts->tcpbind();
	//function call to put server socket to wait for client
	ts->listening();
	while(true)
	{
		//to connect with the client
		ts->tcpaccept();
		if(fork()==0)
		{
			//function call to close the tcp socket
			ts->tcpclosesocket();
			//function call to receive invite
			ts->receiveinvitemsg();
			//fuction call to establish the connection
			ts->sendmsgtotcpclient();
		}
	}
	//releases mutex object
	pthread_mutex_unlock(&x);
	return 0;
}
void *UA_Client(void *param)
{
	//locks the mutex object
	pthread_mutex_lock(&x);
	char **argv=(char**) param;
	//object creation 
	UdpServer *us=new UdpServer(atoi(argv[2]),argv[1]);
	UdpClient *uc=new UdpClient(atoi(argv[2]),argv[1]);
	TcpClient *tc=new TcpClient(atoi(argv[3]),argv[1]);
	int port=atoi(argv[2]);
	int tport=atoi(argv[3]);
	string tipaddr=argv[1];
	//function to create udp socket
	us->createsocket(port,argv[1]);
	//function call to bind
	us->binding();
	//function call to create udp socket
	uc->createsocket(port,argv[1]);
	//function call to create tcp socket
	tc->tcpcreatesocket(tport,tipaddr);
	//function call to connect
	tc->tcpconnect();
	cout<<"------------------------------------------------------------------"<<endl;
	cout<<"                    WELCOME TO SIP APPLICATION                    "<<endl;
	cout<<"------------------------------------------------------------------"<<endl;
	char cusername1[50];
	char cipaddress[20];
	char cusername2[50];
	string invite1,invite2,invitemsg;
	strcpy(cipaddress,argv[1]);
	int reg;
	do
	{
		int c1,c;
		fstream fs;
		string line;
		cout<<endl;
		cout<<endl;
		cout<<"PRESS 1:To REGISTER in server\nPRESS 2:To send INVITE\nPRESS 3:To Exit\nPlease enter your choice:"<<endl;
		cin>>reg;
		switch(reg)
		{
			case 1:
				cout<<"-------------------------------REGISTER------------------------------"<<endl;
				cout<<"Enter the USER AGENT CLIENT register name"<<endl;
				cin>>cusername1;
				c=0;
				//to open file
				fs.open("register.txt", ios::in | ios::out | ios::app);
				//to check whether user is already registered
				while(getline(fs,line))
				{
					if(line.find(cusername1,0)!=string::npos)
					{
						cout<<cusername1<<" is already registered"<<endl;
						c=1;
					}
				}
				//to close file
				fs.close();
				//store the username in file if not already registered
				if(c==0)
				{
					//to open the file
					fs.open("register.txt",ios::in | ios::out |ios::app);
					//to  write into file
					fs<<cusername1<<"|"<<cipaddress<<endl;
					//to close the file
					fs.close();
				}
				cout<<"Enter the USER AGENT SERVER register name:"<<endl;
				cin>>cusername2;
				c1=0;
				//open the file
				fs.open("register.txt", ios::in | ios::out | ios::app);
				//check whether user is already registered or not
        	        	while(getline(fs,line))
        	        	{
		        	        if(line.find(cusername2,0)!=string::npos)
		        	        {
						cout<<cusername2<<" is already registered"<<endl;
						c1=1;
					}
				}
				//close the file
				fs.close();
				if(c1==0)
				{
					//open the file
					fs.open("register.txt",ios::in | ios::out |ios::app);
					//to write into file
					fs<<cusername2<<"|"<<cipaddress<<endl;
					//file close
					fs.close();
				}
				break;
			case 2:
				cout<<"-------------------------------INVITE-------------------------------"<<endl;
				cout<<"Enter the USER AGENT CLIENT register name"<<endl;
				cin>>cusername1;
				c=0;
				c1=0;
				fs.open("register.txt", ios::in | ios::out | ios::app);
				//to get User agent client details
				while(getline(fs,line))
				{
					if(line.find(cusername1,0)!=string::npos)
					{
						invite1=invite1+cusername1+"|"+cipaddress;
						c=1;
					}
				}
				if(c==0)
				{
					cout<<cusername1<<" is not found\nplease PRESS 1 to REGISTER\n----------------------------------------------------"<<endl;
					break;
				}
				fs.close();
				cout<<"Enter the USER AGENT SERVER register name"<<endl;
				cin>>cusername2;
				//to get user agent agent details
				fs.open("register.txt",ios::in|ios::out|ios::app);
				while(getline(fs,line))
				{
					if(line.find(cusername2,0)!=string::npos)
					{
						invite2=invite2+cusername2+"|"+cipaddress;
						c1=1;
					}
				}
				if(c1==0)
				{
					cout<<cusername2<<"is not found\nPlease PRESS 1 to REGISTER\n-----------------------------------------------"<<endl;
					break;
				}
				fs.close();
				invitemsg=invitemsg+invite1+"|"+invite2;
				//function call to send invite
				uc->sendinvitemsg(invitemsg);
				//function call to receive invite
				us->receiveinvitemsg();
				//function call to send response
				us->sendresponsetoudpclient();
				//function call to receive response
				uc->receiveresponsefromudpserver();
				//function call to close socket
				uc->closesocket();
				//function call to close socket
				us->closesocket();
				//function call to send invite
			        tc->sendinvitemsgtoserver(invitemsg);
				//to establish connection and data transfer
			        tc->sendmsgtotcpserver();
				//to close socket
			        tc->tcpclosesocket();
				break;
			case 3:
				exit(0);
			default:
				cout<<"Please enter the choice correctly!!!"<<endl;
		}
	}while(reg!=3);
	//to unlock mutex
	pthread_mutex_unlock(&x);
	//to destroy thread
	pthread_exit(NULL);
	return 0;
}
