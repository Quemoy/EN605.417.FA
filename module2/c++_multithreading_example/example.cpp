#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
 
#define NUM_THREADS     8

// Found at https://en.wikipedia.org/wiki/POSIX_Threads

void* perform_work( void* argument )
{
  int passed_in_value;
 
  passed_in_value = *( ( int* )argument );
  printf( "Hello World! It's me, thread with argument %d!\n", passed_in_value );
 
  struct timespec t;
  t.tv_sec = 1 * passed_in_value;
  t.tv_nsec = 0;
  printf( "Sleeping for %d seconds... \n", passed_in_value);
  nanosleep(&t, NULL);
 
  return NULL;
}
 
int main( int argc, char** argv )
{
  pthread_t threads[ NUM_THREADS ];
  int thread_args[ NUM_THREADS ];
  int result_code;
  unsigned index;
 
  // create all threads one by one
  for( index = 0; index < NUM_THREADS; ++index )
  {
    thread_args[ index ] = index;
    printf("In main: creating thread %d\n", index);
    result_code = pthread_create( &threads[index], NULL, perform_work, &thread_args[index] );
    assert( !result_code );
  }
 
  // wait for each thread to complete
  for( index = 0; index < NUM_THREADS; ++index )
  {
    // block until thread 'index' completes
    result_code = pthread_join( threads[ index ], NULL );
    assert( !result_code );
    printf( "In main: thread %d has completed\n", index );
   }
 
   printf( "In main: All threads completed successfully\n" );
   exit( EXIT_SUCCESS );
}
