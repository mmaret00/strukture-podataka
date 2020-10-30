#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct osoba; //ka jer zna inace bit bug
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
void EnterAfter(Position);
void EnterBefore(Position);
char* nameOfFile(char*);
void EnterIntoFile(Position, char*);
void ScanFromFile(Position, char*);


int main()
{
    char c = 0;
    int m = 0;
	char* fileName = NULL;
	_student Head;
	Head.next = 0;
	//fileName = nameOfFile(fileName);

	while(!m){

    printf("\n1 - add a new student to the beginning of the list\n2 - print the list\n3 - add a new student to the end of the list\n4 - find a student of the list (by last name)\n5 - delete a student from the list\n6 - add a new student after a certain student\n7 - add a new student before a certain student\n8 - print the list into a .txt file\nc - close\n\n");
    scanf(" %c", &c);

    switch (c) {
        case '1':   EnterBeginning(&Head); break;
        case '2':   Print(Head.next); break;
        case '3':   EnterEnd(&Head); break;
        case '4':   Find(&Head);  break;
        case '5':   Delete(&Head);  break;
		case '6':   EnterAfter(&Head);  break;
		case '7':   EnterBefore(&Head);  break;
		case '8':	fileName = nameOfFile(fileName); EnterIntoFile(Head.next, fileName); break;
		case '9':	fileName = nameOfFile(fileName); ScanFromFile(Head.next, fileName); break;
        case 'c':   return 0; m++;

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

//vjezba 3

void EnterAfter(Position p)
{
	Position prev;
	char entry[50] = {0};

	printf("Enter the first name of the person after which you want to add a new student:\n");
	scanf(" %s", entry);

	prev = FindPrev(entry, p);
	prev = prev->next;

	EnterBeginning(prev);
}

void EnterBefore(Position p)
{
	Position prev;
	char entry[50] = {0};

	printf("Enter the first name of the person in front of which you want to add a new student:\n");
	scanf(" %s", entry);

	prev = FindPrev(entry, p);

	EnterBeginning(prev);
}

char* nameOfFile(char* fileName) {

	fileName = (char*)malloc(1024 * sizeof(char));
	printf("Enter the name of the file: \n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}

void EnterIntoFile(Position p, char* fileName){

	FILE* f = NULL;
	f = fopen(fileName, "w");

	while(NULL != p){
		fprintf(f, "%s %s %d\n", p->firstName, p->lastName, p->year);
		p = p->next;
	}
}

void ScanFromFile(Position p, char* fileName){

	Position q = 0;
	FILE* f = NULL;
	f = fopen(fileName, "r");
	puts("prije");
	while(NULL != p->next){
		
		q = (Position)malloc(sizeof(_student));
		
		fscanf(f, " %s %s %d\n", p->firstName, p->lastName, p->year); //PROMINIT OVO
puts("unutar");
		q->next = p->next;
		p->next = q;

		p = p->next;
	}
}
