#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Function prototype works as a way to avoid an error caused by Fibonacci_Recursive
unsigned long long int Fibonacci_Recursive_Memo(int N);

// This list vairable would be our cache storage to be later used by memoization and wrapper functions
unsigned long long int *cacheStorage;

// Iterates the function by N placed into int X
// Variables are set to keep track of current and previous numbers to allow Fibonacci
unsigned long long int Fibonacci_Iterative(int N) {
   unsigned long long int prevNum = 0;
   unsigned long long int saveNum = 0;
   unsigned long long int currNum = 1;

   // Checks to see if Nth is either 1 or 2 to return the right amounts
   // Without any calculation
   if (N == 1) {
      return 0;
   } else if (N == 2) {
    return 1;
   } else {
      for(int i = 2; i <= N; i++) {
        saveNum = prevNum + currNum;
        prevNum = currNum;
        currNum = saveNum;
      }
   }
   return saveNum;
}

// The entirety of Fibonacci_Recursive calls Memo recursively
// With N approaching to it's total amount after several addings of previous numbers
unsigned long long int Fibonacci_Recursive (int N) {
   if (N == 1) {
      return 0;
   } else if (N == 2) {
      return 1;
   } else {
    return Fibonacci_Recursive_Memo(N - 1) + Fibonacci_Recursive_Memo(N - 2);
   }
}

// Checks whether the Nth fibonacci was already calculated with not equalling -1
// If it isn't then it'll be calculated and stored on the cache storage
unsigned long long int Fibonacci_Recursive_Memo(int N) {
   if (cacheStorage[N] != -1) {
      return cacheStorage[N];
   }
   if (N == 1) {
      cacheStorage[1] = 0;
      return 0;
   }
   if (N == 2) {
      cacheStorage[2] = 1;
      return 1;
   }
   
   cacheStorage[N] = Fibonacci_Recursive(N - 1) + Fibonacci_Recursive(N - 2);

   // Later returns the state of the cache over to the wrapper function
   return cacheStorage[N];
}

unsigned long long int Fibonacci_Recursive_Wrapper(int N) {
      // This is a way to set the whole size of the cache
      cacheStorage = malloc((N + 1) * sizeof(unsigned long long int));

      // This loop is intended to set every position from the given Nth
      // -1 represents Nth positions that haven't been calculated yet
      for (int i = 0; i <= N; i++) {
         cacheStorage[i] = -1;
      }

      // TotalFibonacci is received by calling the Memoization with the Nth amount
      unsigned long long int totalFibonacci = Fibonacci_Recursive_Memo(N);

      // Once everything is done with the cache, it then frees up the memory
      free(cacheStorage);

      // Returns the total fibonacci of the Nth amount the user inputted
      return totalFibonacci;
   }

// Main paramaters are utilized to grab command line string to be used through this part
int main(int argc, char* argv[]) {
   
   /*// FILE is used and as a pointer to indicate the usage of the data stored with file
   FILE* file;
   // TextNum is used in order to store the number kept inside the specified text file
   unsigned long long int textNum;

   // Fopen is used to open an existing file
   // Specified by the first paramter with "r" representing read
   file = fopen(argv[3], "r");
   // Fscanf is used to go through the data in file which is then stored into textNum
   fscanf(file, "%d", &textNum);

   if(argv[3] == NULL) {
        printf("No such file has been found\n");
         return 1;
   }*/

   // Both the user command line and the text file numbers are added together
   unsigned long long int N = atoi(argv[1]);
   // N is subtracted by 1 as a required thing in Fibonacci sequencing

   if(strcmp(argv[2], "i") == 0) {
        printf("%llu\n", Fibonacci_Iterative(N)); 
   } else if(strcmp(argv[2], "r") == 0) {
        printf("%llu\n", Fibonacci_Recursive_Wrapper(N));
   }
   return 0;
}