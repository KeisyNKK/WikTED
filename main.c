#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h> //necessário para strcpy
#include "lib/functions.h"

int main(int argc, char *argv[])
{
   catchfunctions(argv[1]);

   printList();
   return 0;
}
