#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
int count = 0;
void* do_stuff(int* param) {
  int* count = (int*) param;
  pthread_mutex_lock(&mutex);
  (*count)++;
  printf("Count was just incremented to: %d\n", *count);

  pthread_mutex_unlock(&mutex);

  return NULL;
}
int main(void) {
  //pthread_mutex_init(&mutex, NULL); **TRYING TO FIGURE OUT WHY THIS IS NEEDED**
  int * x;
  *x = 10;
  pthread_t *p_tids = malloc(sizeof(pthread_t)*5);
  for (int i = 0; i < 5; i++) {
    printf("this is i %d\n", i);
    pthread_create( &p_tids[i], NULL, (void*)do_stuff, &count );
  }  
  for (int j =0; j < 5; j++) {
    pthread_join( p_tids[j], NULL );
  }  
  pthread_mutex_destroy(&mutex);

  return 0;
}