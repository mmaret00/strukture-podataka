#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct tree* postree;
typedef struct stack* posstack;

typedef struct tree {

	char* el;
	postree r;
	postree l;
}_tree;

typedef struct stack {

    postree el;
	posstack next;
}_stack;

int pop(posstack, postree*);
int push(posstack, postree);
int calculate(posstack, FILE*, postree*);
int infix(postree);
int pushTree(postree*);
int make(posstack*);

int main() {

	posstack head = NULL;
	postree root = NULL;
	FILE* f = fopen("postfix", "r");

	make(&head);
	calculate(head, f, &root);
   	infix(root);

	return 0;
}

int pushTree(postree *x){

	postree q = NULL;
	q = (postree)malloc(sizeof(_tree));
	if(NULL == q){
        printf("Allocation error\n");
        return 0;
	}
	q->el = NULL;
	q->l = NULL;
	q->r = NULL;
	*x = q;

	return 0;
}

int make(posstack *x){

	posstack q = NULL;
	q = (posstack)malloc(sizeof(_stack));
	if(NULL == q){
        printf("Allocation error\n");
        return 0;
	}
	q->el = NULL;
	q->next = NULL;
	*x = q;
	return 0;
}

int pop(posstack p, postree *x) {

	posstack temp = NULL;
	postree q = NULL;
	temp = p->next;
	p->next = temp->next;
	q = temp->el;
	free(temp);
	*x = q;

	return 0;
}

int push(posstack p, postree x) {

	posstack q = NULL;
	if(make(&q)) return 0;
	q->el = x;
	q->next = p->next;
	p->next = q;

	return 0;
}

int calculate(posstack p, FILE* f, postree *x) {

	postree q = NULL;
	int n = 0, len = 0;
	char *postfix = NULL;

	postfix = (char*)malloc(MAX_LENGTH * sizeof(char));
	if(NULL == postfix){
        printf("Allocation error\n");
        return 0;
	}


	while (!feof(f)) {

        pushTree(&q);
		fscanf(f, " %s ", postfix);
		len = strlen(postfix);
		q->el = (char*)malloc(sizeof(char) * len);
		if(NULL == q->el){
            printf("Allocation error\n");
            return 0;
        }
		strcpy(q->el, postfix);
		q->l = NULL;
		q->r = NULL;

		len = sscanf(postfix, " %d", &n);
		if(len <= 0) {
			pop(p, &q->r);
			pop(p, &q->l);
		}
		push(p, q);
	}

	fclose(f);
	free(postfix);
    	pop(p, &q);
    	*x = q;
	return 0;
}

int infix(postree p) {

	if (p != NULL) {
        if (NULL != p->l) printf(" ( ");
		infix(p->l);
		printf(" %s", p->el);
		infix(p->r);
        if (NULL != p->r) printf(" ) ");
	}
	return 0;
}
