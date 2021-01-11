#define _CTR_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct tree* position;

typedef struct tree{
	int n;
	position l;
	position r;
}_tree;

position Enter(position, int);
int PrintPrefix(position);
int PrintInfix(position);
int PrintPostfix(position);
position Find(position, position, int);
position Delete(position, int);

int main(){
	
	position head = NULL;
	int num = 1, ext = 0;
	char c;
	
	while(0 == ext){
		
		printf("\n1 - Enter a number; 2 - Print Prefix; 3 - Print Infix; 4 - Print Postfix; 5 - Find a number; 6 - Delete a number; 7 - Exit\n");
		scanf("%c", &c);
		
		switch(c){
			case '1': 
				printf("Which number do you want to enter?: ");
				scanf("%d", &num);
				head = Enter(head, num);
				break;
			case '2': 
				PrintPrefix(head);
				break;
			case '3': 
				PrintInfix(head);
				break;
			case '4': 
				PrintPostfix(head);
				break;
			case '5':
				printf("Which number do you want to find?: ");
				scanf("%d", &num);
				Find(head, head, num);
				break;
			case '6':
				printf("Which number do you want to delete?: ");
				scanf("%d", &num);
				head = Delete(head, num);
				break;
			case '7':
				ext++:
				return 0;
		}
	}
	
	return 0;
}

position Enter(position p, int num){
	
	
	if(NULL == p){
		p = (position)malloc(sizeof(_tree));
		p->n = num;
		p->l = NULL;
		p->r = NULL;
	}
	
	else if (num < p->n) p->l = Enter(p->l, num);
	
	else if (num > p->n) p->r = Enter(p->r, num);
	
	else printf("\nThat number is already in the tree.\n");
	
	return p;
}

int PrintPrefix(position p){
	
	if (NULL != p){
		printf("%d ", p->n);
		PrintPrefix(p->l);
		PrintPrefix(p->r);
	}
	return 0;
}

int PrintInfix(position p){
	
	if (NULL != p){
		PrintInfix(p->l);
		printf("%d ", p->n);
		PrintInfix(p->r);
	}
	return 0;
}

int PrintPostfix(position p){
	
	if (NULL != p){
		PrintPostfix(p->l);
		PrintPostfix(p->r);
		printf("%d ", p->n);
	}
	return 0;
}

position Find(position p, position parent, int num) {

	if (p == NULL) {
		printf("That number is not in the tree.\n");
		return p;
	}

	if (p->n < num) {
		parent = p;
		return Find(p->r, parent, num);
	}
	else if (p->n > num) {
		parent = p;
		return Find(p->l, parent, num);
	}

	else{
		printf("Parent: %d", parent->n);
		if (p->l != NULL) printf("\nLeft child: %d", p->l->n);
		if (p->r != NULL) printf("\nRight child: %d", p->r->n);
		return p;
	}

}

position Delete(position p, int num) {

	position q = NULL;
	position temp = NULL;

	if (NULL == p) return p;
	
	if (num > p->n) p->r = Delete(p->r, num);
	
	else if (num < p->n) p->l = Delete(p->l, num);
	
	else {
		if (p->l != NULL && p->r != NULL) {
			temp = p;
			p = p->l;
			while (p->r != NULL)p = p->r;
			q = p;
			p = temp;
			p->n = q->n;
			p->l = Delete(p->l, q->n);
		}
		else {
			q = p;
			if (p->l == NULL)p = p->r;
			else p = p->l;
			free(q);
		}
	}
	return p;
}
