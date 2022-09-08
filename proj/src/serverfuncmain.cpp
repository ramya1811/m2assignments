#include<functions.h>
int main(int argc,char *argv[])
{
	//thread id
	pthread_t id4;
	//to creat the thread
	if(pthread_create(&id4,NULL,UA_Server,(void*)argv)<0)
	{
		perror("Could not create thread");
		return 1;
	}
	//wait for te thread to complete 
	pthread_join(id4,NULL);
	return 0;
}
