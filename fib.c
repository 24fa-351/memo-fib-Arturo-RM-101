#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Function prototype works as a way to avoid an error caused by Fibonacci_Recursive
unsigned long long int Fibonacci_Recursive_Memo(int Nth);

// This list vairable would be our cache storage to be later used by memoization and wrapper functions
unsigned long long int *Cache_Storage;

// Iterates the function by N placed into int X
// Variables are set to keep track of current and previous numbers to allow Fibonacci
unsigned long long int Fibonacci_Iterative(int Nth) {
   unsigned long long int Prev_Num = 0;
   unsigned long long int Save_Num = 0;
   unsigned long long int Curr_Num = 1;

   // Checks to see if Nth is either 1 or 2 to return the right amounts
   // Without any calculation
   if (Nth == 1) {
      return 0;
   } else if (Nth == 2) {
    return 1;
   } else {
      for(int i = 2; i <= Nth; i++) {
        Save_Num = Prev_Num + Curr_Num;
        Prev_Num = Curr_Num;
        Curr_Num = Save_Num;
      }
   }
   return Save_Num;
}

// The entirety of Fibonacci_Recursive calls Memo recursively
// With N approaching to it's total amount after several addings of previous numbers
unsigned long long int Fibonacci_Recursive (int Nth) {
   if (Nth == 1) {
      return 0;
   } else if (Nth == 2) {
      return 1;
   } else {
    return Fibonacci_Recursive_Memo(Nth - 1) + Fibonacci_Recursive_Memo(Nth - 2);
   }
}

// Checks whether the Nth fibonacci was already calculated with not equalling -1
// If it isn't then it'll be calculated and stored on the cache storage
unsigned long long int Fibonacci_Recursive_Memo(int Nth) {
   if (Cache_Storage[Nth] != -1) {
      return Cache_Storage[Nth];
   }
   if (Nth == 1) {
      Cache_Storage[1] = 0;
      return 0;
   }
   if (Nth == 2) {
      Cache_Storage[2] = 1;
      return 1;
   }
   
   Cache_Storage[Nth] = Fibonacci_Recursive(Nth - 1) + Fibonacci_Recursive(Nth - 2);

   // Later returns the state of the cache over to the wrapper function
   return Cache_Storage[Nth];
}

unsigned long long int Fibonacci_Recursive_Wrapper(int Nth) {
      // This is a way to set the whole size of the cache
      Cache_Storage = malloc((Nth + 1) * sizeof(unsigned long long int));

      // This loop is intended to set every position from the given Nth
      // -1 represents Nth positions that haven't been calculated yet
      for (int i = 0; i <= Nth; i++) {
         Cache_Storage[i] = -1;
      }

      // TotalFibonacci is received by using Memoization with the Nth amount
      unsigned long long int Total_Fibonacci = Fibonacci_Recursive_Memo(Nth);

      // Once everything is done with the cache, it then frees up the memory
      free(Cache_Storage);

      // Returns the total fibonacci of the Nth amount the user inputted
      return Total_Fibonacci;
   }

   unsigned long long int Fibonacci_Iterative_Memo(int Nth) {
   if (Cache_Storage[Nth] != -1) {
      return Cache_Storage[Nth];
   }
   if (Nth == 1) {
      Cache_Storage[1] = 0;
      return 0;
   }
   if (Nth == 2) {
      Cache_Storage[2] = 1;
      return 1;
   }
   
   Cache_Storage[Nth] = Fibonacci_Iterative(Nth);

   // Later returns the state of the cache over to the wrapper function
   return Cache_Storage[Nth];
}

   unsigned long long int Fibonacci_Iterative_Wrapper(int Nth) {
      // This is a way to set the whole size of the cache
      Cache_Storage = malloc((Nth + 1) * sizeof(unsigned long long int));

      // This loop is intended to set every position from the given Nth
      // -1 represents Nth positions that haven't been calculated yet
      for (int i = 0; i <= Nth; i++) {
         Cache_Storage[i] = -1;
      }

      // TotalFibonacci is received by using Memoization with the Nth amount
      unsigned long long int Total_Fibonacci = Fibonacci_Recursive_Memo(Nth);

      // Once everything is done with the cache, it then frees up the memory
      free(Cache_Storage);

      // Returns the total fibonacci of the Nth amount the user inputted
      return Total_Fibonacci;
   }

// Main paramaters are utilized to grab command 
// line string to be used through this part
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

   // Both the user command line and the text file numbers are added together
   unsigned long long int Nth = atoi(argv[1]);
   // N is subtracted by 1 as a required thing in Fibonacci sequencing

   if(strcmp(argv[2], "i") == 0) {
        printf("%llu\n", Fibonacci_Iterative_Wrapper(Nth)); 
   } else if(strcmp(argv[2], "r") == 0) {
        printf("%llu\n", Fibonacci_Recursive_Wrapper(Nth));
   }
   return 0;
}