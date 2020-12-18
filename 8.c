/*Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija. Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i povratak u prethodni direktorij.
Točnije program treba preko menija simulirati korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

//koristit strcmpi (case insensitive)

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024
#define MAX_DIR_LENGTH 256
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef enum _insertResult{
	SUCCESS,
	DUPLICATED_DIRECTORY,
	ALLOCATION_FAILED
}InsertResult;


typedef struct _dir* PosDir;

typedef struct _dir{
	char name[MAX_DIR_LENGTH];
	PosDir child;
	PosDir sibling;
}Dir;


typedef struct _stack* PosStack;

typedef struct _stack {
	PosDir dir;
	PosStack next;
}Stack;

InsertResult md(PosDir, char*);
PosDir createDir(char*);
PosDir insertRec(PosDir current, PosDir el);
int deleteDir(PosDir);
int pushDir(PosStack, PosDir);
PosDir popDir(PosStack);
PosDir findDir(PosDir, char*);



int main(){
	PosDir root = NULL;
	PosDir current = NULL;
	Stack stack;
	stack.next = NULL;

	root = createDir("C:");

	if(NULL == root) return 0;

	//while i switch case

	while(stack.next != NULL)
		popDir(&stack);

	deleteDir(root);

	return 0;
}

PosDir createDir(char* name){

	PosDir dir = NULL;

	dir = malloc(sizeof(Dir));

	if(NULL == dir){
		printf("Allocation failed\n");
		return 0;
	}

	strcpy(dir->name, name);
	dir->child = NULL;
	dir->sibling = NULL;

	return 0;
}

int deleteDir(PosDir current){
	if(NULL == current) return;
	deleteDir(current->sibling);
	deleteDir(current->child);
	free(current);
}

int pushDir(PosStack head, PosDir dir){

	PosStack el = NULL;

	el =(PosStack)malloc(sizeof(Stack));

	if(NULL == el){
		printf("Allocation failed\n");
		return 0;
	}

	el->dir = dir;
	el->next = head->next;
	head->next = el;

	return 0;
}

PosDir popDir(PosStack head){

	PosStack first = head->next;
	PosDir result = NULL;

	if(NULL == first){
		return 0;
	}

	head->next = first->next;
	result = first->dir;
	free(first);

	return result;
}

PosDir findDir(PosDir current, char* name){

	PosDir child = current->child;

	while(child != NULL && strcmp(child->name, name) != 0)
		child = child->sibling;

	return child;
}

InsertResult md(PosDir current, char* name){

	PosDir el = NULL;
	PosDir child = NULL;

	if(findDir(current, name) != NULL) return DUPLICATED_DIRECTORY;

	el = createDir(name);

	if(NULL == el) return ALLOCATION_FAILED;

	if(NULL == current->child){
		current->child = el;
		return SUCCESS;
	}

	if(strcmp(current->child->name, el->name) > 0){
		el->sibling = current->child;
		current->child = el;
		return SUCCESS;
	}

	child = current->child;

	while(child->sibling != NULL && strcmp(child->sibling->name, el->name) < 0)
		child = child->sibling;

	el->sibling = child->sibling;
	child->sibling = el;

	return SUCCESS;
}

PosDir insertRec(PosDir current, PosDir el){

	if(NULL == current) return el;

	if(strcmp(el->name, current->name) < 0){
		el->sibling = current;
		return el;
	}

	current->sibling = insertRec(current->sibling, el);
	return current;
}
