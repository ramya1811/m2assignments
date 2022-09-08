#include<functions.h>
int main(int argc,char *argv[])
{
	//to initialize the mutex
	if(pthread_mutex_init(&x,NULL)!=0)
	{
		perror("Mutex init failed");
		return 1;
	}
	//thread id
	pthread_t id1;
	//create thread to manage user agent client
	if(pthread_create(&id1,NULL,UA_Client,(void *)argv)<0)
	{
		perror("Could not create thread");
		return 1;
	}
	//wait for the thread to complete its process
	pthread_join(id1,NULL);
	//destroy the mutex
	pthread_mutex_destroy(&x);
	return 0;
}
