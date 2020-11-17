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