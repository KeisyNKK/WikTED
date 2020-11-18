
#ifndef PAGE_H_INCLUDED
#define PAGE_H_INCLUDED
#pragma once
#include<stdio.h>
#include "editor.h"
#include "link.h"

typedef struct Page Page;

struct Page
{
   Page* next; //outra pagina
   char* name; //nome do artigo
   char* file; //nome do artigo
   Link link;
   Editor* editor;
   Edit* edit;
};

void insertPage(char name[], char file[]);
struct Page* findPage(char* name); 
void printList();
void deletePage(char name[]);


#endif // PAGE_H_INCLUDED
