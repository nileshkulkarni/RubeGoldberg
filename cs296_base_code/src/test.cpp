
extern "C"{
#include <pthread.h>

}


#include <iostream>
#include<cstdlib>
using namespace std ;

void* function1(void* arg);


int main1( void )
{

   pthread_t  t1,t2 ;

   string msg1 ("hello")  ;
   string msg2 ("world")  ;

   int create1 = pthread_create( &t1, NULL, function1,reinterpret_cast<void*>(&msg1));
    if (create1 != 0) cout << "error" ;
  usleep(1000*100);
   	int create2 = pthread_create( &t2, NULL, function1,reinterpret_cast<void*>(&msg2));
    if (create2 != 0) cout << "error" ;
   pthread_join(t1,NULL) ;
   pthread_join(t2,NULL) ;

   return 0;
}

void* function1(void* arg)
{
    system("mpg123 song.mp3");
	return 0;
}
