#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>

int countparams(char string[])
{
   int i=0;

   if (strcmp(string,  "INSEREPAGINA") == 0) return i = 2;
      
   else if (strcmp(string, "RETIRAPAGINA") == 0) return i = 1;

   else if (strcmp(string, "INSEREEDITOR") == 0) return i = 1;
   
   else if (strcmp(string, "RETIRAREDITOR") == 0) return i = 1;

   else if (strcmp(string, "INSERECONTRIBUICAO") == 0) return i = 3;
      
   else if (strcmp(string, "RETIRACONTRIBUICAO") == 0) return i = 3;
      
   else if (strcmp(string, "INSERELINK") == 0) return i = 2;

   else if (strcmp(string, "RETIRALINK") == 0) return i = 2;

   else if (strcmp(string, "CAMINHO") == 0) return i = 2;
      
   else if (strcmp(string, "IMPRIMEPAGINA") == 0) return i = 1;

   else if (strcmp(string, "FIM") == 0) return i = 0;

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

   char function[100], param[100], file[100];
      
   while(!feof(fp))
   {
        fscanf(fp, "%s " , function);

        printf("\n\nFunction is |%s|\n", function );

        int i = countparams(function);

        for(int j = 0; j<i; j++)
        {
            fscanf(fp, "%s ", param);
            printf("Param is |%s|\n", param );
        }
   }

   fclose(fp);
}