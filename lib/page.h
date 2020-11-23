
#ifndef PAGE_H_INCLUDED
#define PAGE_H_INCLUDED
#pragma once
#include "list.h"

typedef struct Page Page;

struct Page
{
   Page* next; //outra pagina
   char** name; //nome do artigo
   List* edit; //contribuição
   Page* link; //elemento de lista genérico
};

Page* insertPage(char** params, int size, Page* popPage);
Page* deletePage(char name[], Page* popPage);
Page* findPageByName(Page* popPage, char name[]);
Page* findLinkByName(Page* pageLink, char name[]);
void printLink(Page* linkPage);
void reversePage(Page** PageR);


#endif // PAGE_H_INCLUDED


