#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include "list.h"
#include "page.h"
#include "private.h"


void insertEdit(char** params, Page* popPage, List* popEditor)
{
    printf("\n 1) Inserting edit:\n %s %s %s...\n",params[0],params[1],params[2]);

    Page* page = findPageByName(popPage, params[0]);
    
    if(page == NULL) 
    {
        printf("\nPage %s doesn't exist\n", params[0]);
        return ;
    }
    
    printf("\nFound page: %s %s\n", page->name[0],page->name[1]);

    printf("\nLook for editor\n");
    List* editor = findListByName(popEditor,params[1]);

    if(NULL == editor)
    {
        printf("\nEditor not found ! Can't insert \n");
        return;
    }
    printf("\nFound editor: %s \n", editor->name[0]);

    printf("\nLook for edit\n");

    List* edit = findListByName(page->edit, params[2]);
    if(edit != NULL)
    {
        printf("\nThe edit %s already exists \n",edit->name[0] );
        return;
    }
    printf("\nEdit not found, proceding the insertion..\n");
    char** file =(char **)malloc(sizeof(char *));

    file[0] = (char *)malloc( sizeof(char) * (strlen(params[2])+1));

    strcpy(file[0],params[2]);

    printf("\nEditor: %s  \n", editor->name[0]);
    page->edit = insertList(file, 1, page->edit);

    page->edit->reference = editor;
    free(file[0]);
    free(file);
    
    return ;
}


List* deleteEdit(char ** params, List* popEditor, Page* popPage)
{
    printf("Deliting edit %s %s %s...",params[0],params[1],params[2]);

    Page* page = findPageByName(popPage, params[0]);
    
    if(page == NULL) 
    {
        printf("\nPage %s doesn't exist", params[0]);
        return NULL;
    }

    printf("\nPage found: %s %s\n", page->name[0],page->name[1]);

    List* editor = findListByName(popEditor, params[1]);

    if(editor == NULL) 
    {
        printf("\nEditor not found\n");
        return NULL;
    }
    List * edit = findListByName(page->edit, params[2]);
    if(edit == NULL) 
    {
        printf("\n Edit not found\n");
        return NULL;
    }
    else if(strcmp(edit->reference->name[0], params[1]) != 0)
    {
        printf("\n Only %s can delete %s ", edit->reference->name[0], params[1]);
        return NULL;
    }
    List* deleted = findListByName(page->edit, params[2]);
    if(deleted == NULL) 
    {
        printf("\n Edit %s not found on the page %s\n", params[2], page->name[0]);
        return NULL;
    }
    page->edit = deleteList(params[2], page->edit, 1);//Finding the edit file 
    free(deleted);
    free(deleted->name[0]);
    free(deleted->name);

    return page->edit;

}

void insertLink(char** params, Page* popPage)
{
    printf("\nInserting Link %s %s...\n",params[0],params[1]);

    Page* page1 = findPageByName(popPage, params[0]);
    printf("\nFound first page %s\n",page1->name[0]);
    if(page1 == NULL) 
    {
        printf("\nPage %s doesn't exist\n", params[0]);
        return ;
    }
    else if(strcmp(page1->name[0], params[0]) != 0)
    {
        printf("\n %s != %s Can't create link\n", params[0], page1->name[0]);
    }

    Page* page2 = findPageByName(popPage, params[1]);
    
    if(page2 == NULL) 
    {
        printf("\nPage %s doesn't exist\n", params[0]);
        return ;
    }
    
    printf("\nfound: %s %s", page1->name[0],page2->name[0]);

    Page* link = findLinkByName(page1->link,params[1]);
    if(link != NULL)
    {
        printf("\n Link already exist from %s to %s",page1->name[0], link->name[0]);
        return;
    }

    page1->link = insertPage(params, 0, page1->link);
    page1->link->link = page2;
    
    return ;
}

void printPage(Page* popEditor)
{
    printf("\n<print>");  

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
        printLink(page->link);

        page = page->next;
        printf("\n");
    }  
}

void printLink(Page* linkPage)
{
    printf("\n<links>");  

    struct Page *link = linkPage;
	
    //start from the beginning
    while(link != NULL) 
    {   
        printf("\n");
        
        printf("[0] : %s ", (link->link->name)[0]);
        
        link = link->next;
    }    
}

void isLink(char** params,Page* popPage)
{
    printf("\nIs there link %s %s\n", params[0], params[1]);
    Page* page1 = findPageByName(popPage, params[0]);
    if(page1 == NULL)
    {
        printf("\nPage %s not found\n", params[0]);
        return;
    }
    
    Page* page2 = findPageByName(popPage, params[1]);
    if(page2 == NULL)
    {
        printf("\nPage %s not found\n", params[1]);
        return;
    }

    Page* link = findLinkByName(page1->link, params[1]);
    if(link == NULL)
    {
        printf("\nLink not found\n");
        printf("\nThere's no link between them look: %s %s.\n", page1->name[0], page2->name[0]);
        char str[80];
        strcpy(str, "\nNAO HA CAMINHO DA PAGINA ");
        strcat(str, params[0]);
        strcat(str, " PARA ");
        strcat(str, params[1]);
        logg(str);
        return;
    }
    else if(strcmp(link->link->name[0], params[1]) == 0)
    {
        char str[80];
        strcpy(str, "\nHA CAMINHO DA PAGINA ");
        strcat(str, page1->name[0]);
        strcat(str, " PARA ");
        strcat(str, link->link->name[0]);
        logg(str);
        
        return;
    }
    
}

void logg(char* logM)
{
    
    FILE * log;

    log = fopen("log.txt", "a");

    if(log == NULL)
    {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    fputs(logM, log);

    fclose(log);

}