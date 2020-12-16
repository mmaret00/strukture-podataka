//Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa rezultat. Stog je potrebno realizirati preko vezane liste.

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

char* nameOfFile(char*);
int Push(Position, int);
int Pop(Position);
int Calculate(Position, char*);

int main(){
	
	_el head;
	char* fileName = NULL;
	head.next = NULL;
	
	fileName = nameOfFile(fileName);
	Calculate(&head, fileName);
	printf("%d", head.next->n);

	return 0;
}

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


int Push(Position p, int x){

	Position q = NULL;

    while (p->next != NULL) p = p->next;
    
	q = (Position)malloc(sizeof(_el));
	q->n = x;
	q->next = p->next;
	p->next = q;
	return 0;
}

int Pop(Position p) {

	int temp = 0;
	Position q = NULL;
	
	while (p->next->next != NULL) p = p->next;
	
	if (NULL == p->next->next) {
		q = p->next;
		temp = p->next->n;
		p->next = NULL;
		free(q);
		return temp;
	}
	else if (p->next == NULL) {
		q = p->next;
		temp = p->next->n;
		p->next = NULL;
		free(q);
		return temp;
	}
	return 0;
}

int Calculate(Position p, char* fileName){

	FILE* f;
	int x = 0, a = 0, b = 0;
	char postfix[20];
	
	f = fopen(fileName, "r");
	
	while (!feof(f)){

		fscanf(f, "%s", postfix);
		if (postfix[0] >= '0' && postfix[0] <= '9') {
			x = atoi(postfix);
			Push(p, x);
		}
		else {
			a = Pop(p);
			b = Pop(p);
			switch (postfix[0]) {
				case '+':Push(p, a + b); break;
				case '*':Push(p, a * b); break;
				case '-':Push(p, a - b); break;
				case '/':	if(0 == a){
								printf("\nDivision with zero.\n");
								return 0;
							}
							
		Push(p, (float)(a / b)); break;
			}
		}
	}
	return 0;
}
