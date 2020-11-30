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

int Entry(Position);
int Enter(Position, int);
int Print(Position);
Position Previous(Position, Position);
int Delete(Position, Position);
int Union(Position, Position, Position);
int Section(Position, Position, Position);

int main(){
	
	_el head1;
	_el head2;
	_el head3;
	_el head4;
	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;
	head4.next = NULL;


	printf("Entering 1st list\n");
	Entry(&head1);
	printf("Entering 2nd list\n");
	Entry(&head2);

	Section(&head1, &head2, &head3);
	Union(&head1, &head2, &head4);
	
	printf("\nSection:\n");
	Print(head3.next);
	printf("\nUnion:\n");
	Print(head4.next);

	return 0;
}

int Entry(Position Head) {

	int numOfElements = 0, n = 0, i = 0;
	
	printf("How many elements does the list have?\n");
	scanf("%d", &numOfElements);
	
	for(i = 0; i < numOfElements; i++) {
		printf("Member no.%d: ", i + 1);
		scanf("%d", &n);
		Enter(Head, n);
	}
	return 0;
}

int Enter(Position Head, int n){

    Position p = Head;
    Position q = NULL;

    q = (Position)malloc(sizeof(_el));
	if(NULL == q){
        printf("Allocation failed.\n");
        return 0;
    	}

	while (NULL != p->next) p = p->next;
		
	q->n = n;
	
	q->next = p->next;
	p->next = q;
	
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

Position Previous(Position p, Position q){
	
	Position r = p->next;
	Position s = q;
	
	while(NULL != r && r->n != q->n){
		s = r;
		r = r->next;
	}
	if (NULL == r) return 0;
	return s;
}

int Delete(Position p, Position q){
	Position temp = NULL;
	Position r = q;
	
	r = Previous(p, q);
	temp = r->next;
	
	if (NULL != q->next) r->next = NULL;
	else r->next = r->next->next;
	
	free(temp);
	return 0;
}

int Union(Position list1, Position list2, Position list3) { //zeza kad se upise puno brojeva

	Position L1 = list1;
	Position L2 = list2;
	Position L3 = list3;
	
	while (NULL != L1->next && NULL != L2->next) {
		if (L1->next->n == L2->next->n) {
			Delete(list2, L2->next);
			if (L2->next == NULL) break;
			L2 = L2->next;
		}
		else {
			L2 = L2->next;
		}
		if (NULL == L2->next) {
			L1 = L1->next;
			L2 = list2;
		}
	}
	
	L3->next = list1->next;
	while (NULL != L3->next) L3 = L3->next;
	L3->next = list2->next;
	
	return 0;
}

int Section(Position list1, Position list2, Position list4) {
	
	Position L1 = list1;
	Position L2 = list2;
	
	while (NULL != L1->next && NULL != L2->next) {
		if (L1->next->n == L2->next->n) {
			Enter(list4, L2->next->n);
			L2 = L2->next;
		}
		else {
			L2 = L2->next;
		}
		if (L2->next == NULL) {
			L1 = L1->next;
			L2 = list2;
		}
	}
	return 0;
}
