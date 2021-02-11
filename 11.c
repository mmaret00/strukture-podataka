#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct List* poz;
typedef struct List* lista;
typedef struct HashTab* hashTabPoz;

typedef struct List {

	char firstName[10];
	char lastName[20];
	int id;
	int key;
	poz next;
}_list;

typedef struct HashTab {

	int tabSize;
	lista* hashList;
}hashT;

hashTabPoz init(int);
int add(hashTabPoz);
int enter(poz);
int key(poz);
int print(hashTabPoz);
int sorter(char*, char*);
int find(hashTabPoz);

int main() {

	int x = 0;
	hashTabPoz hashTable = NULL;
	hashTable = init(11);
	do {
		printf("\nEnter - 1, print - 2, find - 3, end - 4\n");
		scanf("%d", &x);
		switch (x) {
		case 1:	add(hashTable);
			break;

		case 2:	print(hashTable);
			break;

		case 3:	find(hashTable);
			break;

		case 4:	return 0;
		}
		
	} while (x != 4);
	return 0;
}

int sorter(char* p1, char* p2) {

	int i = 0;
	while (p1[i] != '\0' && p2[i] != '\0') {
		if (p1[i] > p2[i])return 1;
		else if (p1[i] == p2[i])i++;
		else return -1;
	}
	return 0;
}

int find(hashTabPoz hash) {

	lista pathFinder = NULL;
	
	poz p = (poz)malloc(sizeof(_list));
	if (p == NULL) return 0;
	
	printf("\nEnter first and last name:\n");
	scanf("%s %s", p->firstName, p->lastName);
	
	p->key = key(p);
	pathFinder = hash->hashList[p->key];
	
	while (pathFinder != NULL) {
		if (!sorter(pathFinder->firstName, p->firstName) && !sorter(pathFinder->lastName, p->lastName)) break;
		pathFinder = pathFinder->next;
	}
	
	if (pathFinder == NULL) return 0;

	printf("ID: %d", pathFinder->id);

	return 0;

}


int print(hashTabPoz hash) {

	lista printer = NULL;
	int i = 0, br = 0, mb = 0;
	char c = 0;
	
	printf("Do you want to see the ID? (y/n)\n");
	scanf(" %c", &c);
	
	if (c == 'y') mb++;
	else if (c == 'n') mb = 0;
	else { 
		printf("Wrong entry\n");
		return 0; 
	}

	for (i = 0; i < 11; i++) {
		br = 0;
		printer = hash->hashList[i];
		while (printer != NULL) {
			if (!br) {
				printf("\nIndex %d: %s %s", i, printer->firstName, printer->lastName);
				if (mb) printf(" %d", printer->id);
				br++;
			}
			
			else {
				printf(" , %s %s", printer->firstName, printer->lastName);
				if (mb) printf(" %d", printer->id);
			}
			
			printer = printer->next;
		}
	}
	
	return 0;
}

int key(poz q){
	
	int i = 0, sum = 0;
	
	for (i = 0; i < 5; i++) {
		if (*(q->lastName + i) == '\0') break;
		
		sum += *(q->lastName + i);
	}
	
	q->key = sum % 11;

	return q->key;
}

int add(hashTabPoz hash) {

	lista target = NULL;
	poz p = NULL, temp = NULL;
	int Key = 0;
	printf("Type stop to stop.\n");

	while (1) {
		
		target = NULL;
		p = (poz)malloc(sizeof(_list));
		p->next = NULL;
		printf("First name, last name, ID:\n");
		scanf(" %s", p->firstName);
		if (!strcmp(p->firstName, "stop")) break;

		scanf(" %s %d", p->lastName, &p->id);

		Key = key(p);

		target = hash->hashList[Key];

		if (target == NULL) {

			hash->hashList[Key] = p;
		}

		else if ((strcmp(p->lastName, target->lastName) < 0) || ((strcmp(p->lastName, target->lastName) == 0) && (strcmp(p->firstName, target->firstName) < 0))) {
				p->next = target;
				hash->hashList[Key] = p;
		}

		else{
				while (target->next != NULL && (strcmp(p->lastName, target->next->lastName) > 0))
					target = target->next;

				if (strcmp(p->lastName, target->next->lastName) == 0)
					while (target->next != NULL && strcmp(p->lastName, target->next->lastName) == 0 && strcmp(p->firstName, target->firstName) < 0)
						target = target->next;

				temp = target->next;
				target->next = p;
				p->next = temp;
		}
	}
	return 0;
}

hashTabPoz init(int size) {

	int i = 0;
	hashTabPoz h = NULL;
	h = (hashTabPoz)malloc(sizeof(hashT));
	if (h == NULL) {
		printf("Allocation error\n");
		return 0;
	}
	h->tabSize = size;
	h->hashList = (lista*)malloc(h->tabSize * sizeof(lista));
	if (h->hashList == NULL) {
		printf("Error\n");
		return 0;
	}

	for (i = 0; i < h->tabSize; i++) {

		h->hashList[i] = NULL;
	}

	return h;
}
