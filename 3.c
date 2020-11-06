#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student* Position;

typedef struct student{
    char firstName[20];
    char lastName[20];
    char initial;
    int year;
    Position next;
}_student;


int EnterBeginning(Position);
int Print(Position);
int EnterEnd(Position);
int Find(Position);
Position FindPrev(char[], Position);
int Delete(Position);
int EnterAfter(Position);
int EnterBefore(Position);
char* nameOfFile(char*);
int EnterIntoFile(Position, char*);
int ScanFromFile(Position, char*, int);
int numberOfStudents(char*);
Position getInitial(Position);
int Sort(Position);


int main()
{
    char c = 0;
    int m = 0, n = 0;
	char* fileName = NULL;
	_student Head;
	Head.next = 0;

	while(!m){

    printf("\n1 - add a new student to the beginning of the list\n2 - print the list\n3 - add a new student to the end of the list\n");
    printf("4 - find a student of the list (by last name)\n5 - delete a student from the list\n6 - add a new student after a certain student\n");
    printf("7 - add a new student before a certain student\n8 - print the list into a .txt file\n9 - scan students from a .txt file\n");
    printf("s - sort students by last name\nc - close\n\n");
    scanf(" %c", &c);

    switch (c) {
        case '1':   EnterBeginning(&Head); break;
        case '2':   Print(Head.next); break;
        case '3':   EnterEnd(&Head); break;
        case '4':   Find(&Head);  break;
        case '5':   Delete(&Head);  break;
		case '6':   EnterAfter(&Head);  break;
		case '7':   EnterBefore(&Head);  break;
		case '8':	fileName = nameOfFile(fileName);
					EnterIntoFile(Head.next, fileName); break;
		case '9':	fileName = nameOfFile(fileName);
					n = numberOfStudents(fileName);
					ScanFromFile(&Head, fileName, n); break;
		case 's':	Sort(&Head); break;
        case 'c':   return 0; m++;

        }
	}
}

int EnterBeginning(Position p)
{
    Position q = 0;
    printf("When done, type 'stop'.\n");

    while(1){

    q = (Position)malloc(sizeof(_student));
    if(NULL == q){
        printf("Allocation failed.\n");
        return 0;
    }

	printf("First name, last name, birth year:\n");
    scanf(" %s", &q->firstName);

	if(!strcmp(q->firstName,"stop")) break;
    scanf(" %s %d", &q->lastName, &q->year);
    getInitial(q);
    if(!strcmp(q->firstName,"stop")) break;

    q->next = p->next;
    p->next = q;
    }

    return 0;
}

int Print(Position p)
{
	printf("\nList:\n");
    while(p != 0){
        printf("\n%s %s %d\n", p->firstName, p->lastName, p->year);
        p = p->next;
    }

    return 0;
}

int EnterEnd(Position p)
{
    Position q = 0;
    printf("\nwhen done, type 'stop'.\n");

    while(1){

    q = (Position)malloc(sizeof(_student));
    if(NULL == q){
        printf("Allocation failed.\n");
        return 0;
    }

    printf("First name, last name, birth year:\n");
	scanf(" %s", &q->firstName);

	if(!strcmp(q->firstName,"stop")) break;
    scanf(" %s %d", &q->lastName, &q->year);
    getInitial(q);

    while(p->next != 0)
        p = p->next;

    q->next = p->next;
    p->next = q;
    }

    return 0;
}

int Find(Position p)
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

    return 0;
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

int EnterAfter(Position p)
{
	Position prev;
	char entry[50] = {0};

	printf("Enter the first name of the person after which you want to add a new student:\n");
	scanf(" %s", entry);

	prev = FindPrev(entry, p);
	prev = prev->next;

	EnterBeginning(prev);

    return 0;
}

int EnterBefore(Position p)
{
	Position prev;
	char entry[50] = {0};

	printf("Enter the first name of the person in front of which you want to add a new student:\n");
	scanf(" %s", entry);

	prev = FindPrev(entry, p);

	EnterBeginning(prev);

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

int EnterIntoFile(Position p, char* fileName){

	FILE* f = NULL;
	f = fopen(fileName, "w");

	while(NULL != p){
		fprintf(f, "%s %s %d\n", p->firstName, p->lastName, p->year);
		p = p->next;
	}
	
	fclose(f);

    return 0;
}

int ScanFromFile(Position p, char* fileName, int n){

	Position q = 0;
	int i = 0;

	FILE* f = NULL;	
	f = fopen(fileName, "r");

	for (i = 0; i < n-1; i++) { //na visual studiu nije n-1 nego n

		q = (Position)malloc(sizeof(_student));
        if(NULL == q){
            printf("Allocation failed.\n");
            return 0;
        }

		fscanf(f, " %s %s %d", q->firstName, q->lastName, &q->year);
		getInitial(q);

		while (NULL != p->next)
			p = p->next;

		q->next = p->next;
		p->next = q;
	}
	
	fclose(f);

    return 0;
}

int numberOfStudents(char* fileName) {

	int n = 0;
	char temp[1024] = { 0 };
	FILE* f = NULL;
	f = fopen(fileName, "r");

	while (!feof(f)) {

		fgets(temp, 1024, f);
		if (strlen(temp) == 0) continue;
		n++;
	}
	fclose(f);
	return n;
}

Position getInitial(Position p) {
	p->initial = p->lastName[0];
	return p;
}

int Sort(Position p)
{
	Position q = NULL;
	Position prev = NULL;
	Position temp = NULL;
	Position end = NULL;
	
	while (end != p->next) {
		prev = p;
		q = p->next;
		
		while (end != q->next) {
			if (q->initial > q->next->initial) {
				temp = q->next;
				prev->next = temp;
				q->next = temp->next;
				temp->next = q;
				q = temp;
			}
			prev = q;
			q = q->next;
		}
		end = q;
	}
	
	return 0;
}
