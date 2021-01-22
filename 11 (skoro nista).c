#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
/*
//sortirani unos
//q se oni sta se unosi
while(p->next != NULL && strcmp(p->next->prezime, q->prezime) < 0)
		p = p->next;
strcmp(q->ime, p->next->ime) > 0)
	p = p->next;

q->next = p->next;
p->next = q; */

typedef struct list* pos;

typedef struct list{
	int mb;
	char* firstName;
	char* lastName;
	int key;
	pos next;
}_list;

int enter(pos, pos[], FILE*);
pos enterSorted(pos, pos);
int print(pos);

int main(){

	_list head;
	pos k[11];
	int i = 0;
	FILE* f = fopen("studenti.txt", "r");

	head.next = NULL;

	for(i = 0 ; i < 11 ; i++)
		k[i] = i;
	
	enter(&head, k, f);
	printf(head.next);

	return 0;
}
int enter(pos p, pos k[], FILE* f){

	int key = 0, i = 0, maticni = 0;
	char* first = (char*)malloc(sizeof(char) * 1024);
	char* last = (char*)malloc(sizeof(char) * 1024);
	pos q = NULL;
	pos head = p;

	/*
	for(i = 0 ; i < 5 ; i++){
		key += p->lastName[i];
		p = p->next;
	}
	key = key % 11;
	printf("\nkljuc: %d\n", key);
	*/
	
	while(!feof(f)){
		fscanf(f, " %d %s %s ", &maticni, first, last);

		q = (pos)malloc(sizeof(_list));
		q->firstName = (char*)malloc(sizeof(char) * 1024);
		q->lastName = (char*)malloc(sizeof(char) * 1024);
		
		strcpy(q->firstName, first);
		strcpy(q->lastName, last);
		q->mb = maticni;
		
		p = enterSorted(head, q);
	}

	return 0;
}
pos enterSorted(pos p, pos q){

	pos head = p;

	while(p->next != NULL && strcmp(p->next->lastName, q->lastName) < 0)
		p = p->next;

	/*while(strcmp(q->firstName, p->next->firstName) > 0)
		p = p->next; */
	
	q->next = p->next;
	p->next = q; 
		
	return p;
}
int print(pos p){

	while(p != NULL){
		printf("\n%d %s %s", p->mb, p->firstName, p->lastName);
		p = p->next;
	}
	return 0;
}
