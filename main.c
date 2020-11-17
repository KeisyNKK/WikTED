#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h> //necessário para strcpy
#include "lib/functions.h"

int main(int argc, char *argv[])
{
   insertPage("Cavadlo","entrada.txt");
   insertPage("Malu","entrada.txt");
   insertPage("Regis","entrada.txt");
   insertPage("Cavalo","entrada.txt");
   insertPage("sd","entrada.txt");
   insertPage("Cavawelo","entrada.txt");

   printList();
   deletePage("Cavalo");

   printf("\n\n");
   printList();
   return 0;
}
