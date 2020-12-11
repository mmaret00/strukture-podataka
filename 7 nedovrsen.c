//Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa rezultat. Stog je potrebno realizirati preko vezane liste.

/*
S PLOČE

(doma u geany dodat txt iznutra)(nebitno sad)

int value = 0, count = 0;
value = sscanf(buffer, "%d%n", &broj);
buffer += count;

2. način:
fgets(buffer, 1000, f);
fscanf(f, "%s", buffer);
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>

typedef struct element* Position;

typedef struct element{
	int n;
	Position next;
}_el;

char* nameOfFile(char* fileName) {

	fileName = (char*)malloc(1024 * sizeof(char));
    if(NULL == fileName){
        printf("Allocation failed.\n");
        return 0;
    }
	printf("Enter the name of the file: \n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}


int Push(Position p, int n){

	Position q = NULL;

    q = (Position)malloc(sizeof(_el));
    if(NULL == q){
        printf("Allocation failed.\n");
        return 0;
    }
	
	q->n = n;

	q->next = p->next;
	p->next = q;

	return 0;
}

int Read(Position p){

	int value = 0, count = 0, n = 0;
	char* buffer = NULL;
	FILE* f = NULL;	
	f = fopen(fileName, "r");

	buffer = (char*)malloc(1000 * sizeof(char*));
	
	fgets(buffer, 1000, f);
	fscanf(f, " %s", buffer);
	
}
