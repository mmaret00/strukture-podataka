#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student* Position;

typedef struct student{
    char firstName[20];
    char lastName[20];
    int year;
    Position next;
}_student;


void EnterBeginning(Position);
void Print(Position);
void EnterEnd(Position);
void Find(Position);
Position FindPrev(char[], Position);
int Delete(Position);


int main()
{
    char c = 0;
    int m = 0;
	_student Head;
	Head.next = 0;
	while(!m){

    printf("\n1 - add new student to the beginning of the list\n2 - print the list\n3 - add new student to the end of the list\n4 - find a student of the list (by last name)\n5 - delete a student from the list\n6 - close\n\n");
    scanf(" %c", &c);

    switch (c) {
        case '1':   EnterBeginning(&Head); break;
        case '2':   Print(Head.next); break;
        case '3':   EnterEnd(&Head); break;
        case '4':   Find(&Head);  break;
        case '5':   Delete(&Head);  break;
        case '6':   return 0; m++;

        }
	}
}

void EnterBeginning(Position p)
{
    Position q = 0;
    printf("When done, type 'stop'.\n");

    while(1){

    q = (Position)malloc(sizeof(_student));

	printf("First name, last name, birth year:\n");
    scanf(" %s", &q->firstName);

	if(!strcmp(q->firstName,"stop")) break;
    scanf(" %s %d", &q->lastName, &q->year);
    if(!strcmp(q->firstName,"stop")) break;

    q->next = p->next;
    p->next = q;
    }
}

void Print(Position p)
{
	printf("\nList:\n");
    while(p != 0){
        printf("\n%s %s %d\n", p->firstName, p->lastName, p->year);
        p = p->next;
    }
}

void EnterEnd(Position p)
{
    Position q = 0;
    printf("\nwhen done, type 'stop'.\n");

    while(1){

    q = (Position)malloc(sizeof(_student));

    printf("First name, last name, birth year:\n");
	scanf(" %s", &q->firstName);

	if(!strcmp(q->firstName,"stop")) break;
    scanf(" %s %d", &q->lastName, &q->year);

    while(p->next != 0)
        p = p->next;

    q->next = p->next;
    p->next = q;
    }
}

void Find(Position p)
{
	char entry[50] = {0};

	printf("\nEnter last name:\n");
    scanf(" %s", entry);

    while(strcmp(entry, p->lastName)){
        p = p->next;

		if(p->next==NULL){
			printf("\nStudent is not on the list.\n");
			break;
		}
	}
		printf("\n%s %s %d\n", p->firstName, p->lastName, p->year);

}

Position FindPrev(char entry[], Position p){
    Position prev = p;
    p = p->next;
    while(p != NULL && strcmp(entry, p->firstName)){
        prev = p;
        p = p->next;
    }
    if(NULL == p) return 0;
    else return prev;
}

int Delete(Position p)
{
    Position temp = 0;
	char entry[50] = {0};

	printf("\nEnter the first name of the person you want to delete from the list:\n");
    scanf(" %s", entry);

    p = FindPrev(entry, p);
                temp = p->next;
                p->next = p->next->next;
                free(temp);
    return 0;
}


