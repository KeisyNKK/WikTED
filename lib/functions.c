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
   //todo: Free the linked lists first
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
      insertPage(params[0], params[1]);
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
      printf("not implementRETIRAEDITORed");
      return 0;
   }

   if(i == 3500)//INSERECONTRIBUICAO
   {
      printf("not implementedINSERECONTRIBUICAO");
      return 0;
   }
      
   if(i == 3600)//RETIRACONTRIBUICAO
   {
      printf("not implementedRETIRACONTRIBUICAO");
      return 0;
   }
      
   if(i == 2700)//INSERELINK
   {
      printf("not implemeINSERELINKnted");
      return 0;
   }

   if(i == 2800)//RETIRALINK
   {
      printf("not implemeRETIRALINKnted");
      return 0;
   }

   if(i == 2900)//CAMINHO
   {
      printf("not implCAMINHOemented");
      return 0;
   }
      
   if(i == 1100)//IMPRIMEPAGINA
   {
      printf("-not implementIMPRIMEPAGINAed");
      return 0;
   }
  
   if(i == 100)//IMPRIMEWIKED
   {
      printf("-not implemenIMPRIMEWIKEDted");
      return 0;
   }

   if(i == 0)//FIM
   {
      printf(".FIMnot implemented");
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

         printf("Param is |%s|\n", params[j] );
      }

      callfunction(i,params);
   }

   fclose(fp);
}