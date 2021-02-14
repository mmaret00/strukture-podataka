#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

typedef struct lista* poz;
typedef struct lista {

	int id;
	char* ime;
	char* prezime;
	int kljuc;
	poz next;
}_lista;

typedef struct hash* pozh;
typedef struct hash {

	poz* list;
}_hash;

int inic(pozh);
int unos(pozh, int, char*, char*);
int ispis(pozh);
int izracunaKljuc(char*);
int cita(pozh, FILE*);
int pronadi(pozh);

int main(){
	
	_hash h;
	FILE* f = fopen("jedanes", "r");
	if(NULL == f){
		printf("greska u fileu");
		return -1;
	}
	
	inic(&h);
	cita(&h, f);
	
	ispis(&h);

	
	pronadi(&h);
	
	fclose(f);
	
	return 0;
}

int inic(pozh h){
	
	int i = 0;
	
	h->list = (poz*)malloc(sizeof(_lista) * 11);
	if(NULL == h->list){
		printf("greska u alokaciji");
		return -1;
	}
	
	for(i = 0; i < 11; i++){
		
		h->list[i] = NULL;
	}
	
	return 0;
}

int cita(pozh h, FILE* f){
	
	char* ime = NULL;
	char* prezime = NULL;
	int id = 0;
	
	while(!feof(f)){
		
		ime = (char*)malloc(sizeof(char) * 1024);
		if(NULL == ime){
		printf("greska u alokaciji");
		return -1;
		}
		prezime = (char*)malloc(sizeof(char) * 1024);
		if(NULL == prezime){
		printf("greska u alokaciji");
		return -1;
		}
		
		fscanf(f, "%d %s %s ", &id, ime ,prezime);
		
		unos(h, id, ime, prezime);
	}
	
	return 0;
}

int izracunaKljuc(char* prezime){
	
	int kljuc = 0, i = 0;
	
	for(i = 0; i < 5; i++){
		if (!(prezime[i])) break;
		kljuc += prezime[i];
	}
	
	return kljuc%11;
}

int unos(pozh h, int id, char* ime, char* prezime){
	
	poz q = NULL;
	poz p = NULL;
	int kljuc = izracunaKljuc(prezime);
	
	if(NULL == h->list[kljuc]){
		h->list[kljuc] = (poz)malloc(sizeof(_lista));
		if(NULL == h->list[kljuc]){
		printf("greska u alokaciji");
		return -1;
		}
		h->list[kljuc]->next = NULL;
	}
	
	q = (poz)malloc(sizeof(_lista));
	if(NULL == q){
		printf("greska u alokaciji");
		return -1;
		}
	
	q->ime = (char*)malloc(sizeof(char) * 1024);
	if(NULL == q->ime){
		printf("greska u alokaciji");
		return -1;
		}
	q->prezime = (char*)malloc(sizeof(char) * 1024);
	if(NULL == q->prezime){
		printf("greska u alokaciji");
		return -1;
		}
	
	q->id = id;
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->kljuc = kljuc;
	
	p = h->list[kljuc];
	
	while(p->next != NULL && ((strcmp(q->prezime, p->next->prezime) > 0) || ((strcmp(q->prezime, p->next->prezime) == 0) && strcmp(q->ime, p->next->ime) > 0))){
		
		p = p->next;
	}
	
	q->next = p->next;
	p->next = q;
	
	return 0;
}

int ispis(pozh h){
	
	poz head = NULL;
	int i = 0;
	
	for(i = 1; i < 11; i++){
		
		if(h->list[i] != NULL){

			head = h->list[i];

			h->list[i] = h->list[i]->next;
			printf("\nkljuc %i: ", i);
						
			while(h->list[i] != NULL){
				
				printf("%s %s %d, ", h->list[i]->prezime, h->list[i]->ime, h->list[i]->id);
				h->list[i] = h->list[i]->next;
			}
			h->list[i] = head;
		}
	}
	
	return 0;
}

int pronadi(pozh h){
	
	char* ime = (char*)malloc(sizeof(char) * 1024);
	char* prezime = (char*)malloc(sizeof(char) * 1024);
	poz p = NULL;
	int kljuc = 0;
	printf("\nunesi ime i prezime studenta kojeg zelis pronaci:\n");
	scanf("%s %s", ime, prezime);
	
	kljuc = izracunaKljuc(prezime);
	p = h->list[kljuc];
	
	p = p->next;
	
	while(p->next != NULL){
		if(strcmp(p->prezime, prezime) == 0) break;
		p = p->next;
		
		if (NULL == p->next){
			printf("\nnema tog studenta");
			return 0;
			}
		}
	
	printf("\nmaticni broj tog studenta je %d\n", p->id);
	
	return 0;
}
