#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

typedef struct Page Page;
typedef struct Link Link;
typedef struct Editor Editor;
typedef struct Edit Edit;
typedef struct WikED WikED;

struct Editor
{
   Editor* next;
   char* name;   
};


struct Edit
{
   Edit* next;
   char* name;   
};
struct Link
{
   Link* next;
   Page* link;
};


struct Page
{
   Page* next; //outra pagina
   char* name; //nome do artigo
   char* file; //nome do artigo
   Link link;
   Editor* editor;
   Edit* edit;
};


int countparams(char string[]);

void catchfunctions(char argv[]);

void insertPage(char name[], char file[]);

struct Page* findPage(char name[]);

void printList();

void deletePage(char name[]);


//Page* createPage ();


#endif // FUNCTIONS_H_INCLUDED