
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#pragma once
#include<stdio.h>
typedef struct List List;

struct List
{
   List* next; //outra pagina
   char** name; //nome do artigo
   List* reference; //elemento de lista genérico
   char avaiable;
};

List* insertList(char** params, int size, List* popList);
void printList(List* popList, int size);
List* deleteList(char name[], List* popList, int size);
List* findListByName(List* popList, char name[]);
void reverseList(List** ListR);


#endif // LIST_H_INCLUDED


