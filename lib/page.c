#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include "page.h"

Page* insertPage(char** params, int size, Page* popPage)
{
   //creating a new page  
   Page* page = (Page*)malloc(sizeof(Page));

   page->name = (char **)malloc(sizeof(char *)*(size));

    for(int j = 0; j<size; j++)
    {
        page->name[j] = (char *)malloc(sizeof(char)*( (strlen(params[j])+10) ));

        strcpy((page->name)[j],params[j]);

        printf("[%d]: %s ",j, (page->name)[j] );
    }

   page->next = popPage;

   page->link =NULL;
   page->edit =NULL;
   return page;
}



Page* deletePage(char name[], Page* popPage)
{
   printf("deliting %s... \n", name);
   struct Page* currentPage = popPage; //taking the last inserted
   struct Page* previous = NULL;
   
   if(popPage == NULL) {
      printf("Nothing to be delete");
      return popPage;//if none was inserted yet, there's nothing to be deleted

      //todo: create a log (logfile) for this
   }
   //todo: Free the linked lists first
   //searching for the page name
   while(strcmp(currentPage->name[0], name)!=0) {
      
      if(currentPage->next == NULL) {
         printf("Name not found");
         //todo: create a log (logfile) for this

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
   struct Page* currentPage = popPage; //taking the last inserted
   struct Page* previous = NULL;
   
   if(popPage == NULL) {
      return NULL;//if none was inserted yet, there's nothing to be deleted
      //todo: create a log (logfile) for this
   }
   //todo: Free the linked lists first
   //searching for the page name
   while(strcmp(currentPage->name[0], name)!=0) {
      
      if(currentPage->next == NULL) {
         printf("Name not found");
         //todo: create a log (logfile) for this
         return NULL;//if null was found, that's the end of the page
      } else {//if there're some items
         previous = currentPage;//keep the previous 
         currentPage = currentPage->next;//and look for the name in the next one
      }  
   }
   return currentPage;

}
