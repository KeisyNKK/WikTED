#include "page.h"
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>
#include <assert.h>

Page* popPage = NULL;
Page* currentPage = NULL;

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
