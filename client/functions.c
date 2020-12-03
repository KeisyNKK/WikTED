#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include "./functions.h"
#include "../lib/private.h"


Page* popPage = NULL;
List* popEditor = NULL; 
List* popEdit = NULL; 
List* popLink = NULL; 

int countparams(char string[])
{
   int i=1;
   //here's the code to determine what function call
   //and how many params are there:
   //always i/1000 is the number of params

   if (strcmp(string,  "INSEREPAGINA") == 0) return i = 2100;
      
   else if (strcmp(string, "RETIRAPAGINA") == 0) return i = 1200;

   else if (strcmp(string, "INSEREEDITOR") == 0) return i = 1300;
   
   else if (strcmp(string, "RETIRAEDITOR") == 0) return i = 1400;

   else if (strcmp(string, "INSERECONTRIBUICAO") == 0) return i = 3500;
      
   else if (strcmp(string, "RETIRACONTRIBUICAO") == 0) return i = 3600;
      
   else if (strcmp(string, "INSERELINK") == 0) return i = 2700;

   else if (strcmp(string, "RETIRALINK") == 0) return i = 2800;

   else if (strcmp(string, "CAMINHO") == 0) return i = 2900;
      
   else if (strcmp(string, "IMPRIMEPAGINA") == 0) return i = 1100;
   
   else if (strcmp(string, "IMPRIMEWIKED") == 0) return i = 100;

   else if (strcmp(string, "FIM") == 0) return i = 0;

   return i;
}

int callfunction(int i, char** params)
{
   //calling the functions with the ammount of params useful
   if(i==2100)//INSEREPAGINA
   {
      int size = i/1000;
      popPage = insertPage(params, size, popPage);
      return 1;
   }
      

   if(i == 1200)//RETIRAPAGINA
   {  
      int size = i/1000;
      popPage = deletePage(params[0], popPage);
      return 1;
   }

   if(i == 1300)//INSEREEDITOR
   {
      int size = i/1000;

      popEditor = insertList(params, size,popEditor);
      return 1;
   }
   
   if(i == 1400)//RETIRAEDITOR
   {
      int size = i/1000;
      return 1;
   }

   if(i == 3500)//INSERECONTRIBUICAO
   {
      insertEdit(params, popPage, popEditor);
      return 1;
   }
      
   if(i == 3600)//RETIRACONTRIBUICAO
   {
      deleteEdit(params, popEditor, popPage);
      return 1;
   }
      
   if(i == 2700)//INSERELINK
   {
      insertLink(params, popPage);
      return 1;
   }

   if(i == 2800)//RETIRALINK
   {
      deleteLink( params,popPage);
      return 1;
   }

   if(i == 2900)//CAMINHO
   {
      isLink(params,popPage);
      return 1;
   }
      
   if(i == 1100)//IMPRIMEPAGINA
   {
      fprintPage(params, popPage);
      return 1;
   }
  
   if(i == 100)//IMPRIMEWIKED
   {
      printWik(popPage);
      return 1;
   }

   if(i == 0)//FIM
   {
      return 0;
   }

   return i;
}

void catchfunctions(char argv[])
{
   //openining the giver agrv file 
   FILE *entrada;

   entrada = fopen(argv,"r");

   if (entrada == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   //opening the file
   char function[100], param[100], file[100];
      
   while(!feof(entrada))
   {
      //runing line by line
      fscanf(entrada, "%s " , function);

      printf("\n\nFunction is |%s|\n", function );

      //defining the params number
      int i = countparams(function);
      int size = i/1000;
      char **params = (char **)malloc(sizeof(char *)*(size));//allocating the quantity of params

      for(int j = 0; j<size; j++)
      {
         fscanf(entrada, "%s ", param);

         params[j] = (char *)malloc(sizeof(char)*(strlen(param)+1));//alocating the params 

         strcpy(params[j],param);

      }
      if(callfunction(i,params)==0) return;//either calling the funciton or terminating the code.
      for(int j = 0; j<size; j++) free(params[j]);//freeing the memory
      free(params);
      
   }

   fclose(entrada);
}