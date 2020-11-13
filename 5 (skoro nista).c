// Za dvije sortirane liste L1 i L2 (mogu se pročitati iz datoteke ili unijeti ručno, bitno je samo da su sortirane), napisati program koji stvara novu vezanu listu tako da računa: a) uniju, b) presjek. Liste osim pokazivača na slijedeću strukturu imaju i jedan cjelobrojni element, po kojem su sortirane.

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct element* Position;

typedef struct element{
	int n;
	Position next;
}_el;

int Enter(Position);
int Print(Position);
int Sort(Position);

int main(){
	
	_el head1;
	_el head2;
	head1.next = NULL;
	head2.next = NULL;


	printf("entering 1st list\n");
	Enter(&head1);
	//printf("entering 2nd list\n");
	//Enter(&head2);

	printf("\n\n1st list:");
	Print(head1.next);
	//printf("\n\n2nd list:\n");
	//Print(head2.next);

	Sort(head1.next);
	Print(head1.next);


	return 0;
}

int Enter(Position p){

    Position q = NULL;
    printf("\nwhen done, type '0'.\n");

    while(1){

    q = (Position)malloc(sizeof(_el));

	scanf("%d", &q->n);

	if(0 == q->n) break;

    while(p->next != 0)
        p = p->next;

    q->next = p->next;
    p->next = q;
    }
	return 0;
}

int Print(Position p){

    while(p != 0){
        printf("\n%d ", p->n);
        p = p->next;
    }
	printf("\n\n");
	return 0;
}

int Sort(Position p){ //prelos, napravit sortirani unos

	Position q = NULL;
	int x;
	q = p->next;

	while(1){ puts("a");
		if(p->n > q->n){
			x = p->n;
			p->n = q->n;
			q->n = x;
			//q->next = p->next;
			//p->next = q;
		}
		if(NULL == p->next) break;
		p = p->next;
	}
	return 0;
}

//obrisa sortirani unos, triba ispocetka
