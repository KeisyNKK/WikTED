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
    
    Page* page = findPageByName(popPage, params[0]);
    
    if(page == NULL) 
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[INSERIRCONTRIBUICAO]: Não existe a página ");
        strcat(loggM, params[0]);
        logg(loggM);
        return ;
    }

    List* editor = findListByName(popEditor,params[1]);

    if(NULL == editor)
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[INSERIRCONTRIBUICAO]:Não é possíve inserir contribuição, pois não existe contribuidor ");
        strcat(loggM, editor->name[0]);
        logg(loggM);
        return;
    }

    List* edit = findListByName(page->edit, params[2]);
    if(edit != NULL)
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[INSERIRCONTRIBUICAO]:Cada contribuição deve ser unica, não permitido inserir novamente ");
        strcat(loggM, edit->name[0]);
        logg(loggM);
        return;
    }

    char** file =(char **)malloc(sizeof(char *));

    file[0] = (char *)malloc( sizeof(char) * (strlen(params[2])+1));

    strcpy(file[0],params[2]);

    page->edit = insertList(file, 1, page->edit);

    page->edit->reference = editor;
    free(file[0]);
    free(file);
    
    return ;
}


List* deleteEdit(char ** params, List* popEditor, Page* popPage)
{

    Page* page = findPageByName(popPage, params[0]);
    
    if(page == NULL) 
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[RETIRACONTRIBUICAO]: Não foi encontrada a página ");
        strcat(loggM, params[0]);
        logg(loggM);
        return NULL;
    }

    List* editor = findListByName(popEditor, params[1]);

    if(editor == NULL) 
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[RETIRACONTRIBUICAO]: Não foi encontrada editor ");
        strcat(loggM, params[1]);
        logg(loggM);
        return NULL;
    }
    List * edit = findListByName(page->edit, params[2]);
    if(edit == NULL) 
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[RETIRACONTRIBUICAO]: Não foi encontrada a contribuição ");
        strcat(loggM, params[1]);
        logg(loggM);
        return NULL;
    }
    else if(strcmp(edit->reference->name[0], params[1]) != 0)
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[RETIRACONTRIBUICAO]: A página  ");
        strcat(loggM, params[0]);
        strcat(loggM, " apenas pode ser deletada por ");
        strcat(loggM, edit->reference->name[0]);
        logg(loggM);
        return NULL;
    }
    List* deleted = findListByName(page->edit, params[2]);
    if(deleted == NULL) 
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[RETIRACONTRIBUICAO]: A contribuição  ");
        strcat(loggM, params[2]);
        strcat(loggM, " não pertence á página ");
        strcat(loggM, params[0]);
        logg(loggM);
        return NULL;
    }
    //it's just flag that the edit isn't supposed to be shown
    page->edit->avaiable = 0;

    return page->edit;
}

void insertLink(char** params, Page* popPage)
{
    
    Page* page1 = findPageByName(popPage, params[0]);

    if(page1 == NULL) 
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[INSERIRLINK]: Não foi encontrada a página  ");
        strcat(loggM, params[0]);
        logg(loggM);
        return ;
    }

    Page* page2 = findPageByName(popPage, params[1]);
    
    if(page2 == NULL) 
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[INSERIRLINK]: Não foi encontrada a página  ");
        strcat(loggM, params[1]);
        logg(loggM);
        return ;
    }

    Page* link = findLinkByName(page1->link,params[1]);
    if(link != NULL)
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[INSERIRLINK]: Já existe link entre  ");
        strcat(loggM, params[0]);
        strcat(loggM, " e ");
        strcat(loggM, params[1]);
        logg(loggM);
        return;
    }
    //same as inserting some page, but it's just meant to point to an actual page that contains it's data.
    page1->link = insertPage(params, 0, page1->link);
    page1->link->link = page2;
    
    return ;
}

void deleteLink(char ** params, Page* popPage)
{
    //same as deleting normal nodes, but in this case the reference isn't in the actual structure, but in the page 
    //but the page is preserved
    Page* page = findPageByName(popPage, params[0]);

    if(page->link == NULL)
    {
        char loggM[100];
        strcpy(loggM, "\nERRO[RETIRARLINK]: Não existem links na página  ");
        strcat(loggM, params[0]);
        logg(loggM);
        return;
    }

    struct Page* currentLink = page->link; //taking the last inserted
    //todo: Free the linked Pages first
    //searching for the page name
    Page* previousLink;


    while(strcmp(currentLink->link->name[0], params[1]) != 0) {

        if(currentLink->next == NULL) {
            char loggM[100];
            strcpy(loggM, "\nERRO[RETIRARLINK]: Não foi econtrado o link entre ");
            strcat(loggM, params[0]);
            strcat(loggM, " e ");
            strcat(loggM, params[1]);
            logg(loggM);
           
            return ;//if null was found, that's the end of the page
        } else {//if there're some items
            previousLink = currentLink;
            currentLink = currentLink->next;//and look for the name in the next one
        }  
    }

   if(currentLink == page->link) {//in case it's the last inserted
      page->link = page->link->next;//just point it to the next
   } else {//otherwise
      previousLink->next = currentLink->next;//make the previous point to the next one
   }
   
   
   free(currentLink);
   return ;
}

void isLink(char** params,Page* popPage)
{
    //just finde and tell if there's a link between two pages
    Page* page1 = findPageByName(popPage, params[0]);
    if(page1 == NULL)
    {
        char loggM[100];
        strcpy(loggM, "\nERRO: Pagina ");
        strcat(loggM, params[1]);
        strcat(loggM, "não foi inserida.");
        logg(loggM);
        return;
    }
    
    Page* page2 = findPageByName(popPage, params[1]);
    if(page2 == NULL)
    {   
        char loggM[100];
        strcpy(loggM, "\nERRO: Pagina ");
        strcat(loggM, params[1]);
        strcat(loggM, "não foi inserida.");
        logg(loggM);
        return;
    }

    Page* link = findLinkByName(page1->link, params[1]);
    if(link == NULL)
    {
        char loggM[50];
        strcpy(loggM, "\nNAO HA CAMINHO DA PAGINA ");
        strcat(loggM, params[0]);
        strcat(loggM, " PARA ");
        strcat(loggM, params[1]);
        logg(loggM);
        return;
    }
    else if(strcmp(link->link->name[0], params[1]) == 0)
    {
        char loggM[80];
        strcpy(loggM, "\nHA CAMINHO DA PAGINA ");
        strcat(loggM, page1->name[0]);
        strcat(loggM, " PARA ");
        strcat(loggM, link->link->name[0]);
        logg(loggM);
        
        return;
    }
    
}

void logg(char* logM)
{
    //update the log file each problem.
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

void fprintPage(char ** params, Page* popPage)
{/*
    Fisica

    --> Historico de contribuicoes
    Pedro c1.txt
    Maria c2.txt
    Pedro c3.txt

    --> Links
    Artes artes.txt

    --> Textos

    -------- c1.txt (Pedro) --------
*/
    FILE * file;
    //calls the print to an individual page
    Page* page = findPageByName(popPage, params[0]);
    printPg(page);

}

void printWik(Page* popPage)
{
    //calls printPg to all pages
    Page* page = popPage;
    while(page != NULL)
    {
        printPg(page);
        page = page->next;
    }
}

void printPg(Page* page)
{
    FILE* file;
     file = fopen(page->name[1], "w");
    
    if(file == NULL)
    {
        char loggM[100];
        strcpy(loggM, "\nERRO: Não foi possível criar/abrir o arquivo ");
        strcat(loggM, page->name[1]);
        logg(loggM);
        exit(EXIT_FAILURE);
    }

    fprintf(file,"\n%s\n",page->name[0]);
    fprintf(file,"\n--> Historico de contribuicoes\n");

    reverseList(&page->edit);
    List* edit = page->edit;
    while(edit != NULL)
    {
        fprintf(file,"%s %s %s\n",edit->reference->name[0], edit->name[0],  edit->avaiable == 1 ? " " : "<<retirada>>");
        edit = edit->next;
    }

    fprintf(file,"\n--> Links\n");
   
    reversePage(&page->link);
    Page* link = page->link;
    while (link != NULL)
    {
        fprintf(file,"%s %s\n",link->link->name[0], link->link->name[1]);
        link = link->next;
    }
    
    fprintf(file,"\n--> Textos\n");

    edit = page->edit;
    while (edit != NULL)
    {
        if(edit->avaiable != 1) 
        {   
            edit = edit->next;
            continue;
        }
        fprintf(file,"\n-------- %s (%s) --------\n", edit->name[0],edit->reference->name[0]);
        FILE *piece;
    
        piece = fopen(edit->name[0], "r");
        if (piece == NULL){
            char loggM[100];
            strcpy(loggM, "\nERRO: Não foi possível criar/abrir o arquivo ");
            strcat(loggM, edit->name[0]);
            logg(loggM);
        }
        char letter;
        fputc('\n', file);
        while( ( letter = fgetc(piece) ) != EOF ) fputc(letter, file);
        fputc('\n', file);
        edit = edit->next;

    }
    

    fclose(file);
}

void freeAll(Page* popPage, List* popEditor)
{
    Page* page;
    List* editor;
    Page* link;
    List* edit;

    while(popPage != NULL || popEditor != NULL )
    {
        page = popPage;
        editor = popEditor;
        
        
        while(page->link != NULL || page->edit != NULL)
        {
            edit = page->edit;
            link = page->link;
            page->link  != NULL ? page->link  = page->link->next : NULL;
            page->edit != NULL ? page->edit = page->edit->next : NULL;

            free(link->name[0]);
            free(link->name);
            free(link);
            free(edit->name[0]);
            free(edit->name);
            free(edit);
        }
        
        popPage != NULL ? popPage = popPage->next : NULL;
        popEditor != NULL ? popEditor = popEditor->next : NULL;

        free(page->name[0]);
        free(page->name[1]);
        free(editor->name[0]);
        free(editor->name);
        free(editor);
        free(page);
    }
}
