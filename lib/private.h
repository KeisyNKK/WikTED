
#ifndef PRIVATE_H_INCLUDED
#define PRIVATE_H_INCLUDED
#pragma once
#include<stdio.h>
#include "list.h"
#include "page.h"

List* insertEdit(char** params, Page* popPage, int size, List* popEditor, List* popEdit);
void printPage(Page* popEditor);
List* deleteEdit(char ** params, List* popEditor, Page* popPage);

#endif // PRIVATE_H_INCLUDED
