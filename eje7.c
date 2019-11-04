#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h>
pthread_mutex_t lock;
pthread_mutex_t mutex [100] = PTHREAD_MUTEX_INITIALIZER;

//Estructura para enviar varios argumentos
struct args {
    int* array;
    int numero;
};


// C program for implementation of Bubble sort 
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void *bubbleSort(void *arguments) 
{ 
    
    //printf("BUBBLE1\n");
    struct args *args = arguments;
    int n = args->numero;
   int i, j; 
   for (i = 0; i < n-1; i++)       
    {
     // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++){ 
           pthread_mutex_lock(&mutex[j]);
            pthread_mutex_lock(&mutex[j+1]);
           if (args->array[j] > args->array[j+1]){ 
              swap(&(args->array[j]), &(args->array[j+1]));
           }
           pthread_mutex_unlock(&mutex[j]);
            pthread_mutex_unlock(&mutex[j+1]);
          }
    }          
    
    return NULL;
} 
  
/* Function to print an array */
void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 

void *bubbleSortInv(void *arguments) 
{ 
    
    //printf("Bubble2\n");
   struct args *args = arguments;
    int n = args->numero;
   int i, j; 
   for (i = 0; i < n-1; i++){       
       // Last i elements are already in place    
       for (j = n-1; j > 0; j--){ 
           pthread_mutex_lock(&mutex[j]);
            pthread_mutex_lock(&mutex[j-1]);
           if (args->array[j-1] > args->array[j]){
              swap(&(args->array[j-1]), &(args->array[j]));
           }
             pthread_mutex_unlock(&mutex[j]);
            pthread_mutex_unlock(&mutex[j-1]);
       }
   }
  
    return NULL;
} 

void *askNumbers(void *vargp) 
{ 
    int numeros;
    printf("¿Cuantos números va a meter?\n");
    scanf("%d",&numeros);
    
    int arr[numeros];
    printf("Ingrese los números:\n");
    for(int i=0;i<numeros;i++){
        scanf("%d",&arr[i]);
    }
    int n = sizeof(arr)/sizeof(arr[0]); 
    
    struct args *Args = (struct args *)malloc(sizeof(struct args));
    Args->array = arr;
    Args->numero = n;
    
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &bubbleSort, (void *)Args);
    
    pthread_t thread_id2;
    pthread_create(&thread_id2, NULL, &bubbleSortInv, (void *)Args);
    
    
    pthread_join(thread_id,NULL);
    pthread_join(thread_id2,NULL);
    //bubbleSort(arr, n); 
    //bubbleSortInv(arr,n);
    printf("Sorted array: \n"); 
    printArray(Args->array, n); 
    return NULL; 
} 
   
int main() 
{ 
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    
    pthread_t thread_id; 
    pthread_create(&thread_id, NULL, askNumbers, NULL); 
    pthread_join(thread_id, NULL); 
    
    pthread_mutex_destroy(&lock);
     
    exit(0); 
}
