#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include "page.h"
#include "private.h"

Page* insertPage(char** params, int size, Page* popPage)
{
   //creating a new page  - same as inserting nomral linked lists
   Page* page = (Page*)malloc(sizeof(Page));

   if(size>0) 
   {
      page->name = (char **)malloc(sizeof(char *)*(size));

      for(int j = 0; j<size; j++)
      {
         page->name[j] = (char *)malloc(sizeof(char)*( (strlen(params[j])+10) ));

         strcpy((page->name)[j],params[j]);
      }
   }

   page->next = popPage;

   page->link =NULL;
   page->edit =NULL;
   return page;
}


Page* deletePage(char name[], Page* popPage)
{
   struct Page* currentPage = popPage; //taking the last inserted
   struct Page* previous = NULL;
   
   //todo: go trhough th Wik and delete de links to this page
   //delete the edits as well

   if(popPage == NULL) {
      char str[80];
      strcpy(str, "\nERRO: NAO HA PAGINAS PARA DELETAR. ");
      logg(str);
      return popPage;//if none was inserted yet, there's nothing to be deleted

      //todo: create a log (logfile) for this
   }
   //todo: Free the linked Pages first
   //searching for the page name
   while(strcmp(currentPage->name[0], name)!=0) {
      
      if(currentPage->next == NULL) {
         char str[80];
         strcpy(str, "\nERRO: não existe a pagina ");
         strcat(str, name);
         logg(str);

         return popPage;//if null was found, that's the end of the page
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
   return popPage;

}

Page* findPageByName(Page* popPage, char name[])
{
   
   if(popPage == NULL) {
      return NULL;
   }
   
   struct Page* currentPage = popPage; //taking the last inserted
   //searching for the page name
   while(strcmp(currentPage->name[0], name)!=0) {      
      if(currentPage->next == NULL) {
         return NULL;//if null was found, that's the end of the page
      } else {//if there's something
         currentPage = currentPage->next;//and look for the name in the next one
      }  
   }
   return currentPage;

}

Page* findLinkByName(Page* pageLink, char name[])
{    
   if(pageLink == NULL) {
      return NULL;//if none was inserted yet, there's nothing to be deleted
      //todo: create a log (logfile) for this
   }
   struct Page* currentLink = pageLink; //taking the last inserted
   //todo: Free the linked Pages first
   //searching for the page name
   while(strcmp(currentLink->link->name[0], name) != 0) {

      if(currentLink->next == NULL) {
         //todo: create a log (logfile) for this
         return NULL;//if null was found, that's the end of the page
      } else {//if there're some items

         currentLink = currentLink->next;//and look for the name in the next one
      }  
   }
   return currentLink;
}

void reversePage(Page** PageR) 
{
   //Just reversing the list 
   Page* prev   = NULL;
   Page* current = *PageR;
   Page* next;
	
   while (current != NULL) {
      next  = current->next;
      current->next = prev;   
      prev = current;
      current = next;
   }
	
   *PageR = prev;
}
