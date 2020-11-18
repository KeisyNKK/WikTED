#include "editor.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>
#include <assert.h>
#include <assert.h>

Editor* popEditor = NULL;
Editor* currentEditor = NULL;

void insertEditor(char name[])
{
   //creating a new editor  
   Editor* editor = (Editor*)malloc(sizeof(Editor));

   editor->name = malloc(strlen(name) + 1);//allocating the space for the string
   strcpy(editor->name, name);             //pasting it

   assert(stricmp(editor->name,name)==0);

   editor->next = popEditor;

   popEditor = editor;

}
