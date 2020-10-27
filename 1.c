#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_LENGTH 1024

typedef struct {
	char firstName[20];
	char lastName[20];
	int points;
	float relativePoints;
}Student;

char* nameOfFile(char*);
Student* allocation(char*, Student*, int);
int numberOfStudents(char*);
int readStudents(char*, Student*, int);
int average(Student*, int);
int printStudents(Student*, int);

int main() {
	int n = 0;
	char* fileName = NULL;
	Student* student = NULL;

	fileName = nameOfFile(fileName);

	n = numberOfStudents(fileName);

	student = allocation(fileName, student, n);
	readStudents(fileName, student, n);
	printStudents(student, n);
	return 0;
}

char* nameOfFile(char* fileName) {

	fileName = (char*)malloc(MAX_LENGTH * sizeof(char));
	memset(fileName, '\0', MAX_LENGTH);
	printf("Enter file name\n");
	scanf("%s", fileName);
	if (strchr(fileName, '.') == NULL)strcat(fileName, ".txt");
	return fileName;
}

Student* allocation(char* fileName, Student* student, int n) {

	FILE* f = NULL;
	f = fopen(fileName, "r");
	student = (Student*)malloc(n * sizeof(Student));
	fclose(f);
	return student;
}

int numberOfStudents(char* fileName) {

	int n = 0;
	char temp[MAX_LENGTH] = { 0 };
	FILE* f = NULL;
	f = fopen(fileName, "r");

	while (!feof(f)) {

		fgets(temp, MAX_LENGTH, f);
		if (strlen(temp) == 0) continue;
		n++;
	}
	fclose(f);
	return n + 1;
}

int readStudents(char* fileName, Student* student, int n) {

	int i = 0;
	FILE* f = NULL;
	f = fopen(fileName, "r");
	for (i = 0; i < n; i++) {

		fscanf(f, "%d %s %s", &student[i].points, student[i].firstName, student[i].lastName);
	}
	fclose(f);

	return 0;
}

int average(Student* student, int n) {

	int i = 0;
	int max = student[0].points;
	for (i = 0; i < n; i++) {
		if (student[i].points > max)max = student[i].points;
	}
	return max;
}

int printStudents(Student* student, int n) {

	int i = 0;
	for (i = 0; i < n - 1; i++) {
		student[i].relativePoints = (float)student[i].points / average(student, n) * 100;
		printf("%d %.2f %s %s\n", student[i].points, student[i].relativePoints, student[i].firstName, student[i].lastName);
	}
	return 0;
}
