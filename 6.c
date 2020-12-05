//Napisati program koji pomoću vezanih listi simulira rad: a) stoga, b) reda.		Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 -100.

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

int Push(Position);
int Print(Position);
int PopStack(Position);
int PopQueue(Position);

int main(){
	_el head;
	char i = 0;
	int end = 0;
	head.next = NULL;
	srand(time(NULL));

	while(!end){

	printf("1 - Push, 2 - Pop Stack, 3 - Pop Queue, 4 - Exit\n");
	scanf(" %c", &i);
		switch(i){
			case '1': Push(&head); Print(head.next); break;
			case '2': PopStack(&head); Print(head.next); break;
			case '3': PopQueue(&head); Print(head.next); break;
			case '4': return 0;
		}
	}

	return 0;
}

int Push(Position p){

	Position q = NULL;
	int n = 0;

    q = (Position)malloc(sizeof(_el));
    if(NULL == q){
        printf("Allocation failed.\n");
        return 0;
    }
	
	n = rand() % 91 + 10;
	q->n = n;

	q->next = p->next;
	p->next = q;

	return 0;
}
int Print(Position p){

	printf("Stack:\n");
	while(p != NULL){
		printf("%d ", p->n);
		p = p->next;
	}
	printf("\n");

	return 0;
}
int PopQueue(Position p){

	Position q = NULL;
	int temp;

	while( p->next != NULL){
		q = p;
		p = p->next;
	}
	temp = p->n;
	q->next = NULL;

	free(p);

	return temp;
}
int PopStack(Position p){

	Position q = NULL;
	int temp;

	q = p->next;
	p->next = p->next->next;

	temp = q->n;

	free(q);

	return temp;
}
