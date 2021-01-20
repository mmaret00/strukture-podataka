#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct list* pos;
typedef struct stack* posstack;

typedef struct list {

	char name[20];
	int root;
	pos next;
	pos child;
}_list;

typedef struct stack {
	pos adress;
	posstack next;
}_stack;

int enter(pos);
pos shift(pos, posstack);
int printDirectories(posstack);
pos pop(posstack);
int push(posstack, pos);
pos goBack(posstack);
int subdirectories(pos);

int main() {

	_list tree;
	pos current = &tree;
	_stack head;
	char choice[20];
	tree.child = NULL;
	tree.next = NULL;
	tree.root = 1;
	printf("Enter root name: ");
	scanf(" %s", tree.name);
	head.next = NULL;
	push(&head, &tree);

	while (1) {

		printf("\n\nmd-make directory\t   cd-change directory\t  dir-print directories\t  cd..-go back\t\texit-exit the program\n\n");
		printDirectories(head.next);
		scanf(" %s", choice);

		if(!strcmp(choice, "md"))
			enter(current);

		else if(!strcmp(choice, "cd")){
			current = shift(current, &head);
			printDirectories(head.next);
		}

		else if(!strcmp(choice, "dir"))
			subdirectories(current);

		else if(!strcmp(choice, "cd..")){
			current = goBack(&head);
			printDirectories(head.next);
		}

		else if(!strcmp(choice, "exit"))
			return 0;

        else printf("Wrong entry.\n");
		}

	return 0;
}

pos goBack(posstack s) {

	pos p = pop(s);
	return p;
}

int subdirectories(pos p) {

	printf("Subdirectories:\n");
	p = p->child;
	if(NULL == p){
		printf("Directory is empty.\n");
		return 0;
	}
	printf("%s\n", p->name);
	p = p->next;

	while (p != NULL) {
		printf("%s\n", p->name);
		p = p->next;
	}
	return 0;
}

int enter(pos p) {
	pos q = NULL;
	char* name = NULL;
	scanf(" %s", name);
	q = (pos)malloc(sizeof(_list));
	if(NULL == q){
		printf("Allocation error\n");
		return 0;
	}
	strcpy(q->name, name);
	if (NULL == p->child) {
		p->child = q;
		q->next = NULL;
		q->root = 0;
		q->child = NULL;
	}
	else {
		p = p->child;

		while (p->next != NULL)  p = p->next;
		q->next = p->next;
		p->next = q;
		q->child = NULL;
		q->root = 1;
	}

	return 0;
}

pos shift(pos p, posstack q) {
	pos tree = p;
	char nameOfDir[20];

	scanf(" %s", nameOfDir);


	p = tree;
	p = p->child;
	while (p != NULL) {
		if (!strcmp(nameOfDir, p->name)) {
			push(q, p);
			return p;
		}
		else p = p->next;
	}

}

int push(posstack p, pos x) {

	posstack q = NULL;
	while (p->next != NULL) p = p->next;
	q = (posstack)malloc(sizeof(_stack));
	if(NULL == q){
		printf("Allocation error\n");
		return 0;
	}
	q->adress = x;
	q->next = p->next;
	p->next = q;
	return 0;
}

pos pop(posstack p) {

	posstack temp = p;
	posstack q = NULL;
	while (p->next->next != NULL)p = p->next;
	if(p->next->adress->root != 1){
		q = p->next;
		temp = p;
		p->next = NULL;
		free(q);
		return temp->adress;
	}
	else {
		printf("You cannot pop the root.\n");
		return p->next->adress;
	}
	return NULL;
}

int printDirectories(posstack p){

	while (p != NULL) {
		if(p->adress->root) printf("%s", p->adress->name);
		else printf(" :\\ %s", p->adress->name);
		p = p->next;
	}
	printf(">");
	return 0;
}
