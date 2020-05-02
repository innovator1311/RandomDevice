#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 10  
int main(){

   // open device file
   int file = open("/dev/RandomDevice", 0);
   if (file < 0){
      printf("Can not open device file");
      return -1;
   }

   // read device file
   char random_number[10];
   int stat = read(file, random_number, BUFFER_LENGTH);
   printf("The random number is:  %s\n",random_number);

   return 0;
}

