#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include "list.h"
#include "private.h"

List* insertList(char** params, int size, List* popList)
{

   //creating a new list  
   List* list = (List*)malloc(sizeof(List));

   if(size>0) 
   {
      list->name = (char **)malloc(sizeof(char *)*(size));

      for(int j = 0; j<size; j++)
      {
         list->name[j] = (char *)malloc(sizeof(char)*( (strlen(params[j])+10) ));

         strcpy((list->name)[j],params[j]);

      }
   }
   list->avaiable = 1;
   list->next = popList;
   list->reference = NULL;

   return list;
}

List* deleteList(char name[], List* popList, int size)
{
   struct List* currentList = popList; //taking the last inserted
   struct List* previous = NULL;
   

   if(popList == NULL) {
      //if none was inserted yet, there's nothing to be deleted
      char loggM[80];
      strcpy(loggM, "\nNão é possível deletar ");
      strcat(loggM, name);
      strcat(loggM, " pois não há páginas ");
      logg(loggM);

      logg(loggM);
      return popList;
      //todo: create a log (logfile) for this
   }
   //todo: Free the linked lists first
   //searching for the List name
   while(strcmp(currentList->name[0], name)!=0) {

      if(currentList->next == NULL) {
         char loggM[80];
         strcpy(loggM, "\nNão foi encontrado ");
         strcat(loggM, name);
         strcat(loggM, " nas páginas");
         logg(loggM);
         //todo: create a log (logfile) for this

         return popList;//if null was found, that's the end of the List
      } else {//if there're some items
         previous = currentList;//keep the previous 
         currentList = currentList->next;//and look for the name in the next one
      }  
   }
   
   if(currentList == popList) {//in case it's the last inserted
      popList = popList->next;//just point it to the next
   } else {//otherwise
      previous->next = currentList->next;//make the previous point to the next one
   }
   for(int i = 0; i<size; i++) free(currentList->name[i]);
   
   free(currentList->name);
   
   free(currentList);
   return popList;
}

List* findListByName(List* popList, char name[])
{
   
   if(popList == NULL) {
      return NULL;//if none was inserted yet, there's nothing to be deleted
      //todo: create a log (logfile) for this
   }

   struct List* currentList = popList; //taking the last inserted

   //searching for the list name
   while(strcmp(currentList->name[0], name)!=0) {

      if(currentList->next == NULL) {

         //todo: create a log (logfile) for this
         return NULL;//if null was found, that's the end of the List
      } else {//if there're some items

         currentList = currentList->next;//and look for the name in the next one
      }  
   }

   return currentList;

}

void reverseList(List** ListR) 
{
   List* prev   = NULL;
   List* current = *ListR;
   List* next;
	
   while (current != NULL) {
      next  = current->next;
      current->next = prev;   
      prev = current;
      current = next;
   }
	
   *ListR = prev;
}