#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define SIZE 256
using namespace std;
double* getints(char*,int*);

char * getchars(char*,int*);
double* removeint(double*, int*,int);
char* remove_char(char*, int*,int);
int main()
{
	setlocale(LC_ALL, "Russian");
	char buf[SIZE] = { 0 }, *text = NULL;
	FILE* in = fopen("Input.txt", "rt");// ��������� ����
	int i = 0;
	/* ������ ����������  */
	text = (char*)calloc(1, sizeof(char));
	while (fgets(buf, SIZE, in) != NULL)
	{
		if (i % 2 == 0 )
			text = (char*)realloc(text, SIZE * (i + 2));
			strcat(text, buf);
		++i;
	}
	/*   �������� �� ������ ����� � �����  */
	int am_int = 0;
	int am_ch = 0;
	double* ints=getints(text,&am_int); 
	char* chars = getchars(text, &am_ch);
	/* ����� ��������, ������ ����� ��������� ��� �������� ��������� � �������,
	   �.�. ��� ����� ��������� ���������, ��� ����� ���������� �� ������ � ���� 
	   * � / � ��������� ��������������� ��������.
	*/
		for (int i = 0; i < am_ch; i++){
			if (chars[i] == '*' || chars[i] == '/'){
				if (chars[i] == '*'){
					double tmp = ints[i] * ints[i + 1];
					chars = remove_char(chars, &am_ch, i);
					ints = removeint(ints, &am_int, (i + 1));
					ints[i] = tmp;
					i--;
				}
				else if (chars[i] == '/'){
					double tmp = ints[i] / ints[i + 1];
					chars = remove_char(chars, &am_ch, i);
					ints = removeint(ints, &am_int, (i + 1));
					ints[i] = tmp;
					i--;
				}
			}
		}
		/* ��� �������������� �������� ���������, �������� ����� ����� ����������. */
	double sum=0.0;
	for (int i = 0; i < am_int; i++){
		sum += ints[i];
	}
	/* ���������� ��, ��������� ����, ���������� �����. */
	FILE* out = fopen("Output.txt", "wt");
	fprintf(out, "%lf", sum);
	/* �� �������� ������� ���� � ���������� ������� �����. */
	fclose(in);
	fclose(out);
	free(text);
	free(chars);
	free(ints);
	system("pause");
	return 0;
}

double* getints(char*p,int* amount){
	int i = 0;
	double * ints = (double*)calloc(1, sizeof(double)); //������� ������������ ������ ��� ����� �����
	while (*p) { 
		if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1)))) { //������� �����
			
			*(ints+i) = strtol(p, &p, 10); //���������� � ������
			i++;
			ints = (double*)realloc(ints, (i*sizeof(double) + sizeof(double))); //��������� ������
			
		}
		else {
			
			p++;
		}
	}
	*amount = i;
	return ints;
}
char* getchars(char* p, int* amount){
	char * chars = (char*)calloc(1, sizeof(char)); // ������� ������������ ������
	int j = 0, i = 0;
	while (*p){
		// ������� �����
		if (*(p + i) == '-' || *(p + i) == '+' || *(p + i) == '*' || *(p + i) == '/'){
			chars[j] = p[i]; // ���������
			j++;
			chars = (char*)realloc(chars, (j*sizeof(char) + sizeof(char)));//��������� ������
			p++;
		}
		else{ p++; };
			
	}
	*amount = j;
	return chars;
}

double* removeint(double*ints, int*amount,int index){
	/*
		������� ����� ����� ��������� ��������� � ������� ����
	*/
	double* new_ints = new double[*(amount) - 1];
	for (int i=0; i < index; i++){
		new_ints[i] = ints[i];
	}
	for (int i = (index+1); i < *(amount); i++){
		new_ints[i-1] = ints[i];
	}
	*(amount) = *(amount) -1;
	free(ints);
	return new_ints;
}
char* remove_char(char*chars, int*amount, int index){
	/*
		������� �������� ����� * � / ����� ��������� ��������� ����
		*/
	char* new_chars = new char[*(amount)-1];
	for (int i = 0; i < index; i++){
		new_chars[i] = chars[i];
	}
	for (int i = ++index; i < *(amount); i++){
		new_chars[i - 1] = chars[i];
	}
	*(amount) = *(amount)-1;
	free(chars);
	return new_chars;
}
