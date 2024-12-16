#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Function prototype works as a way to avoid an error caused by Fibonacci_Recursive
unsigned long long int Fibonacci_Recursive_Memo(int fib_num);

// This list vairable would be our cache storage to be later used by memoization and wrapper functions
unsigned long long int *Cache_Storage;

unsigned long long int Fibonacci_Iterative(int fib_num) {
   unsigned long long int prev_num = 0;
   unsigned long long int save_num = 0;
   unsigned long long int curr_num = 1;

   // Checks to see if Nth is either 1 or 2 to return the right amounts
   // Without any calculation
   if (fib_num == 1) {
      return 0;
   } else if (fib_num == 2) {
    return 1;
   } else {
      for(int ix = 2; ix <= fib_num; ix++) {
        save_num = prev_num + curr_num;
        prev_num = curr_num;
        curr_num = save_num;
      }
   }
   return save_num;
}

// The entirety of Fibonacci_Recursive calls Memo recursively
unsigned long long int Fibonacci_Recursive (int fib_num) {
   if (fib_num == 1) {
      return 0;
   } else if (fib_num == 2) {
      return 1;
   } else {
    return Fibonacci_Recursive_Memo(fib_num - 1) + Fibonacci_Recursive_Memo(fib_num - 2);
   }
}

// If it isn't calculated then it'll be calculated and stored on the cache storage
unsigned long long int Fibonacci_Recursive_Memo(int fib_num) {

   if (Cache_Storage[fib_num] != -1) {
      return Cache_Storage[fib_num];
   }
   if (fib_num == 1) {
      Cache_Storage[1] = 0;
      return 0;
   }
   if (fib_num == 2) {
      Cache_Storage[2] = 1;
      return 1;
   }
   
   Cache_Storage[fib_num] = Fibonacci_Recursive(fib_num - 1) + Fibonacci_Recursive(fib_num - 2);

   return Cache_Storage[fib_num];

}

unsigned long long int Fibonacci_Recursive_Wrapper(int fib_num) {

      Cache_Storage = malloc((fib_num + 1) * sizeof(unsigned long long int));

      // -1 represents Nth positions that haven't been calculated yet
      for (int ix = 0; ix <= fib_num; ix++) {
         Cache_Storage[ix] = -1;
      }

      unsigned long long int total_fibonacci = Fibonacci_Recursive_Memo(fib_num);

      free(Cache_Storage);

      return total_fibonacci;
      }

unsigned long long int Fibonacci_Iterative_Memo(int fib_num) {

   if (Cache_Storage[fib_num] != -1) {
      return Cache_Storage[fib_num];
   }

   if (fib_num == 1) {
      Cache_Storage[1] = 0;
      return 0;
   }

   if (fib_num == 2) {
      Cache_Storage[2] = 1;
      return 1;
   }
   
   Cache_Storage[fib_num] = Fibonacci_Iterative(fib_num);

   return Cache_Storage[fib_num];

}

unsigned long long int Fibonacci_Iterative_Wrapper(int fib_num) {

   // This is a way to set the whole size of the cache
   Cache_Storage = malloc((fib_num + 1) * sizeof(unsigned long long int));

   for (int ix = 0; ix <= fib_num; ix++) {
      Cache_Storage[ix] = -1;
   }

   // TotalFibonacci is received by using Memoization with the Nth amount
   unsigned long long int total_fibonacci = Fibonacci_Recursive_Memo(fib_num);

   // Once everything is done with the cache, it then frees up the memory
   free(Cache_Storage);

   return total_fibonacci;
}

int main(int argc, char* argv[]) {
   
   // Text processing code is commented for testing

   /*// FILE is used and as a pointer to indicate the usage 
   // of the data stored with file
   FILE* file;
   // TextNum is used in order to store the number kept
   // inside the specified text file
   unsigned long long int Text_Num;

   // Fopen is used to open an existing file
   // Specified by the first paramter with "r" representing read
   file = fopen(argv[3], "r");
   // Fscanf is used to go through the data in file then stored into textNum
   fscanf(file, "%llu", &Text_Num);

   if(argv[3] == NULL) {
        printf("No such file has been found\n");
         return 1;
   }*/

   unsigned long long int fib_num = atoi(argv[1]);

   if(strcmp(argv[2], "i") == 0) {
        printf("%llu\n", Fibonacci_Iterative_Wrapper(fib_num)); 
   } else if(strcmp(argv[2], "r") == 0) {
        printf("%llu\n", Fibonacci_Recursive_Wrapper(fib_num));
   }

   return 0;

}