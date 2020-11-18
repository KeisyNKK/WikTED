
#ifndef LINK_H_INCLUDED
#define LINK_H_INCLUDED
#pragma once
#include<stdio.h>
#include "page.h"

typedef struct Link Link;
struct Link
{
   Link* next;
   char* link;
};


#endif // EDITOR_H_INCLUDED
