#include<functions.h>
int main(int argc,char *argv[])
{
	thread worker_UC(Udp_Client,argv);
	thread worker_US(Udp_Server,argv);
	thread worker_TC(Tcp_Client,argv);
	worker_UC.join();
	worker_US.join();
	worker_TC.join();
	return 0;
}
