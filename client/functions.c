#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include<assert.h>
#include "./functions.h"
#include "../lib/list.h"

//namePage: 0 and fileName: 1
//poits to
//contributions (node)
//links

//Link list
//namePage

//contributions list
//fileName 0
//points to
//Editor (node)


//Editor List
//name 0
//contribution node

List* popPage = NULL;


int countparams(char string[])
{
   int i=0;

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
   if (i==0) return 500;//

   if(i==2100)//INSEREPAGINA
   {
      printf("oi");
      int size = i/1000;
      popPage = insertList(params, size, popPage);
      printf("\n\nnt param %d: %s ",1, (popPage->name)[0]);

      printList(popPage,size);
      return 1;
   }
      
   if(i == 1200)//RETIRAPAGINA
   {
      printf("not implementRETIRAPAGINAed");
      return 0;
   }

   if(i == 1300)//INSEREEDITOR
   {
      printf("not implementINSEREEDITORed");
      return 0;
   }
   
   if(i == 1400)//RETIRAEDITOR
   {
      printf("RETIRAEDITOR not implemented");
      return 0;
   }

   if(i == 3500)//INSERECONTRIBUICAO
   {
      printf("INSERECONTRIBUICAO not implemented");
      return 0;
   }
      
   if(i == 3600)//RETIRACONTRIBUICAO
   {
      printf("RETIRACONTRIBUICAO not implemented");
      return 0;
   }
      
   if(i == 2700)//INSERELINK
   {
      printf("INSERELINK not implemented");
      return 0;
   }

   if(i == 2800)//RETIRALINK
   {
      printf("RETIRALINK not implemented");
      return 0;
   }

   if(i == 2900)//CAMINHO
   {
      printf("CAMINHO not implemented");
      return 0;
   }
      
   if(i == 1100)//IMPRIMEPAGINA
   {
      printf("IMPRIMEPAGINA not implemented");
      return 0;
   }
  
   if(i == 100)//IMPRIMEWIKED
   {
      printf("IMPRIMEWIKED not implemented");
      return 0;
   }

   if(i == 0)//FIM
   {
      printf("FIM not implemented");
      return 0;
   }

   return i;
}

void catchfunctions(char argv[])
{
   FILE *fp;

   fp = fopen(argv,"r");

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   //opening the file
   char function[100], param[100], file[100];
      
   while(!feof(fp))
   {
      fscanf(fp, "%s " , function);

      printf("\n\nFunction is |%s|\n", function );

      int i = countparams(function);
      int size = i/1000;
      char **params = (char **)malloc(sizeof(char *)*(size));

      for(int j = 0; j<size; j++)
      {
         fscanf(fp, "%s ", param);

         params[j] = (char *)malloc(sizeof(char)*(strlen(param)+1));

         strcpy(params[j],param);

      }
      callfunction(i,params);
   }

   fclose(fp);
}