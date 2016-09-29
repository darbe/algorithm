#include<stdio.h>
#include<pthread.h>
#define BUFFER_SIZE 4
#define NUM  10
#define OVER (-1)
struct Cache{
	int buffer[BUFFER_SIZE];
	int rid, wid;
	pthread_mutex_t lock;
	pthread_cond_t isEmpty;
	pthread_cond_t isFull;
} ;
void init(struct Cache *p){
	p->rid = p->wid = 0;
	pthread_mutex_init(&p->lock,NULL);
	pthread_cond_init(&p->isEmpty,NULL);
	pthread_cond_init(&p->isFull,NULL);
}
void put(struct Cache *p, int data){
	pthread_mutex_lock(&p->lock);
	while((p->wid + 1) % BUFFER_SIZE == p->rid){
		pthread_cond_wait(&p->isFull,&p->lock);
	}
	p->buffer[p->wid++] = data;
	p->wid = (p->wid == BUFFER_SIZE) ? 0 : p->wid;
	pthread_cond_signal(&p->isEmpty);
	pthread_mutex_unlock(&p->lock);
}

int get(struct Cache * p){
	pthread_mutex_lock(&p->lock);
	while(p->wid == p->rid){
		pthread_cond_wait(&p->isEmpty,&p->lock);
	}
	int val = p->buffer[p->rid++];
	p->rid = (p->rid == BUFFER_SIZE) ? 0 : p->rid;
	pthread_cond_signal(&p->isFull);
	pthread_mutex_unlock(&p->lock);
	return val;
}


void * produce( void *c){
	Cache * p = (Cache*)c;
	for(int i = 0; i < NUM; i++){
		put(p,i);
		printf("produce : %d \n",i);
	}
	put(p,OVER);
	return NULL;
}
void* consume(void *c){
	Cache *p = (Cache*)c;
	while(true){
		int val = get(p);
		if(val == OVER)break;
		printf("consume : %d \n",val)	;
	}
	return NULL;
}


int main(){
	pthread_t producer;
	pthread_t consumer;
	Cache p;
	void * retval;
	init(&p);
	pthread_create(&producer, NULL,produce, (void*)&p);
	pthread_create(&consumer, NULL,consume, (void*)&p);
	pthread_join(producer,&retval);
	pthread_join(consumer,&retval);
	return 0;
}
	
