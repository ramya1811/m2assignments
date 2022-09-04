#include<functions.h>
int main(int argc,char *argv[])
{
	thread worker_TS(Tcp_Server,argv);
	worker_TS.join();
	return 0;
}
