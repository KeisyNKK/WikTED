#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>
#include <assert.h>
#include <assert.h>
#include "functions.h"

Editor* popEditor = NULL;
Editor* currentEditor = NULL;

Edit* popEdit = NULL;
Edit* currentEdit = NULL;
Link* popLink = NULL;
Link* currentLink = NULL;

Page* popPage  = NULL;
Page* currentPage  = NULL;


void insertPage(char name[], char file[])
{
   //creating a new page  
   Page* page = (Page*)malloc(sizeof(Page));

   page->name = malloc(strlen(name) + 1);//allocating the space for the string
   strcpy(page->name, name);             //pasting it

   page->file = malloc(strlen(file) + 1);
   strcpy(page->file, file);

   assert(stricmp(page->name,name)==0);

   page->next = popPage;

   popPage = page;

}

struct Page* findPage(char* name) 
{

   //start from the first link
   struct Page* currentPage = popPage;

   //if list is empty
   if(popPage == NULL) {
      return NULL;
   }

   //navigate through list
   while(!stricmp(name,currentPage->name)) {
	
      //if it is last Page
      if(currentPage->next == NULL) {
         return NULL;
      } else {
         //go to next link
         currentPage = currentPage->next;
      }
   }      
	
   //if data found, return the currentPage Link
   return currentPage;
}

void printList() 
{
   struct Page *ptr = popPage;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%s,%s) ",ptr->name,ptr->file);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

void deletePage(char name[])
{
   struct Page* currentPage = popPage; //taking the last inserted
   struct Page* previous = NULL;
   
   if(popPage == NULL) {
      return;//if none was inserted yet, there's nothing to be deleted
      printf("Nothing to be delete");
      //todo: create a log (logfile) for this
   }

   //searching for the page name
   while(strcmp(currentPage->name, name)!=0) {

      if(currentPage->next == NULL) {
         return ;//if null was found, that's the end of the list
      } else {//if there're some items
         previous = currentPage;//keep the previous 
         currentPage = currentPage->next;//and look for the name in the next one
      }
   }
   if(currentPage == popPage) {//in case it's the last inserted
      popPage = popPage->next;//just point it to the next
   } else {//otherwise
      previous->next = currentPage->next;//make the previous point to the next one
   }    
   free(currentPage);
}

int countparams(char string[])
{
   int i=0;

   if (strcmp(string,  "INSEREPAGINA") == 0) return i = 21;
      
   else if (strcmp(string, "RETIRAPAGINA") == 0) return i = 12;

   else if (strcmp(string, "INSEREEDITOR") == 0) return i = 13;
   
   else if (strcmp(string, "RETIRAEDITOR") == 0) return i = 14;

   else if (strcmp(string, "INSERECONTRIBUICAO") == 0) return i = 35;
      
   else if (strcmp(string, "RETIRACONTRIBUICAO") == 0) return i = 36;
      
   else if (strcmp(string, "INSERELINK") == 0) return i = 27;

   else if (strcmp(string, "RETIRALINK") == 0) return i = 28;

   else if (strcmp(string, "CAMINHO") == 0) return i = 29;
      
   else if (strcmp(string, "IMPRIMEPAGINA") == 0) return i = 10;

   else if (strcmp(string, "FIM") == 0) return i = 0;

   return i;
}

int callfunction(int i, char** params)
{
   if (i==0) return 500;

   if(i==21)
   {
      insertPage(params[0], params[1]);
   }
      
   if(i == 12)
   {
      return 0;
   }

   if(i == 13)
   {
      return 0;
   }
   
   if(i == 14)
   {
      return 0;
   }

   if(i == 35)
   {
      return 0;
   }
      
   if(i == 36)
   {
      return 0;
   }
      
   if(i == 27)
   {
      return 0;
   }

   if(i == 28)
   {
      return 0;
   }

   if(i == 29)
   {
      return 0;
   }
      
   if(i == 10)
   {
      return 0;
   }

   if(i == 0)
   {
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
      int size = i/10;
      char **params = (char **)malloc(sizeof(char *)*(size));

      for(int j = 0; j<size; j++)
      {
         fscanf(fp, "%s ", param);

         params[j] = (char *)malloc(sizeof(char)*(strlen(param)+1));

         strcpy(params[j],param);

         printf("Param is |%s|\n", params[j] );
      }

      callfunction(i,params);
   }

   fclose(fp);
}