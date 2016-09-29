#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


#define FALSE 0
#define TRUE 1


void* readfun(void *);
void* writefun(void *);


char buffer[256];
int buffer_has_item=0;
int retflag=FALSE,i=0;
pthread_mutex_t mutex;





void* readfun(void *p){
	while(1){
		if(retflag)
			return NULL;
		pthread_mutex_lock(&mutex);
		if(buffer_has_item==1){
			printf("%s",buffer);
			buffer_has_item=0;
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
void* writefun(void* p){
	int i=0;
	while(1){
		if(i==10){
			retflag=TRUE;
			return NULL;
		}
		pthread_mutex_lock(&mutex);
		if(buffer_has_item==0){
			sprintf(buffer,"This is %d\n",i++);
			buffer_has_item=1;
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(){
	void *retval;
	pthread_t reader;
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&reader,NULL,readfun,NULL);
	writefun(NULL);
	pthread_join(reader,&retval);
}
