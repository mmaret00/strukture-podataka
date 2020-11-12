#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct polynomial* Position;

typedef struct polynomial{
	int n;
	int x;
	Position next;
}_pol;

char* nameOfFile(char*);
int Allocation(Position*);
int Scan(Position);
int Print(Position);
int Addition(Position, Position, Position);
int Multiplication(Position, Position, Position);


int main() {

	_pol head1;
	_pol head2;
	_pol add;
	_pol mult;

	head1.next = NULL;
	head2.next = NULL;
	add.next = NULL;
	mult.next = NULL;

	printf("\nFirst polynomial:\n");
	Scan(&head1);
	printf("\nSecond polynomial:\n");
	Scan(&head2);

	printf("\nFirst polynomial:\n");
	Print(head1.next);

	printf("\n\nSecond polynomial:\n");
	Print(head2.next);

	Addition(head1.next, head2.next, &add);
	printf("\n\nSum:\n");
	Print(add.next);

	Multiplication(head1.next, head2.next, &mult);
	printf("\n\nProduct:\n");
	Print(mult.next);
	puts("");

	return 0;
}

char* nameOfFile(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));

	printf("Name of file:\n");
	scanf(" %s", fileName);

	if (NULL == strchr(fileName, '.'))strcat(fileName, ".txt");
	return fileName;
}

int Allocation(Position *head)
{
	Position q = NULL;

	*head = (Position)malloc(sizeof(_pol));

	q = *head;
	q->next = NULL;

	return 0;
}

int Scan(Position r) {

	Position q = NULL, p = NULL;
	FILE* f = NULL;
	char* fileName = NULL;

	fileName = (char*)malloc(sizeof(char) * MAX_LENGTH);
	if (NULL == fileName) return 0;

	fileName = nameOfFile(fileName);
	f = fopen(fileName, "r");
	if (NULL == f) {
		printf("Error with opening file\n"); //bolje napisat
		return 0;
	}

	while (!feof(f)) {

        Allocation(&q);

        fscanf(f, " %d %d", &q->n, &q->x);

        p = r;
		while (p->next != NULL && p->next->x > q->x)
        p = p->next;

		if (p->next != NULL && p->next->x == q->x)
		{
			p->next->n += q->n;
			free(q);

			if (0 == p->next->n)
			{
				q = p->next;
				p->next = q->next;
				free(q);
			}
		}
		else
		{
			q->next = p->next;
			p->next = q;
		}
    }
    fclose(f);
	return 0;
}

int Print(Position p) {

    int i = 1;

	while (p != NULL) {
        if(i){
            printf("%d*x^%d", p->n, p->x);
            i = 0;
        }
        else if(p->x > 0) printf(" + %d*x^%d", p->n, p->x);
        else    printf(" + %d", p->n);
		p = p->next;
	}
	return 0;
}

int Addition(Position p, Position q, Position add) {

	Position r = NULL;

	while (p != NULL && q != 0) {
            Allocation(&r);

			if (p->x > q->x) {
				r->x = p->x;
				r->n = p->n;
				p = p->next;
			}
			else if (q->x > p->x) {
				r->x = q->x;
				r->n = q->n;
				q = q->next;
			}
			else if (p->x == q->x) {
				r->x = p->x;
				r->n = p->n + q->n;
				p = p->next;
				q = q->next;
			}

        r->next = add->next;
        add->next = r;
        add = r;
}
    return 0;
}

int Multiplication(Position first, Position second, Position mult)
{
    Position q = NULL;
    Position f = NULL;
    Position s = NULL;
    Position mul = NULL;

    f = first;
    while(f != 0){
            s = second;

            while(s != 0){
                Allocation(&q);
                mul = mult;

                q->x = f->x + s->x;
                q->n = f->n * s->n;

                while(mul->next != NULL && mul->next->x > q->x)    mul = mul->next;

                if(mul->next != NULL && mul->next->x == q->x){
                    mul->next->n += q->n;
                    free(q);

                    if(0 == mul->next->n){
                        q = mul->next;
                        mul->next = q->next;
                        free(q);
                    }
                }
                else{
                    q->next = mul->next;
                    mul->next = q;
                }
                s = s->next;
            }
            f = f->next;
    }
    return 0;
}
//mozda dodat da se prvo sortira pa onda zbroji/pomnozi, pitat u petak
