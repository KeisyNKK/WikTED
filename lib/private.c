#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include "../lib/list.h"
#include "../lib/page.h"


List* insertEdit(char** params, Page* popPage, int size, List* popEditor, List* popEdit)
{
    printf("Inserting edit %s %s %s...",params[0],params[1],params[2]);

    Page* page = findPageByName(popPage, params[0]);
    
    if(page == NULL) 
    {
        printf("Page %s doesn't exist", params[0]);
        return popEdit;
    }
    
    printf("\nfound: %s %s", page->name[0],page->name[1]);

    char** file =(char **)malloc(sizeof(char *)*(size));

    file[0] = (char *)malloc( sizeof(char) * (strlen(params[2])+1) );

    strcpy(file[0],params[2]);

    List* editor = findListByName(popEditor,params[1]);

    printf("editor: %s\n", editor->name[0]);
    List* inserted = editor->reference = page->edit = insertList(file, 1, page->edit);

    inserted->reference = editor;
    
    return inserted;
}

List* deleteEdit(char ** params, List* popEditor, Page* popPage)
{
    printf("Deliting edit %s %s %s...",params[0],params[1],params[2]);

    Page* page = findPageByName(popPage, params[0]);

    if(page == NULL) 
    {
        printf("Page %s doesn't exist", params[0]);
        return NULL;
    }

    printf("\nfound: %s %s", page->name[0],page->name[1]);

    page->edit = deleteList(params[2], page->edit);//Finding the edit file 

    return popEditor = deleteList(params[1], popEditor);

}

void printPage(Page* popEditor)
{
    printf("\n<print>\n");  

    struct Page *page = popEditor;
	
    //start from the beginning
    while(page != NULL) 
    {   
        printf("\n");
        for(int j = 0; j<2; j++)
        {
            printf("[%d] : %s ",j, (page->name)[j]);
        }
        printList(page->edit,1);
        printList(page->link,1);

        page = page->next;
    }  
}