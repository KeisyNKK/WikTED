#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED
#pragma once
#include<stdio.h>
#include "edit.h"

typedef struct Editor Editor;

struct Editor
{
   Editor* next;
   char* name;   
   Edit edit;
};



#endif // EDITOR_H_INCLUDED
