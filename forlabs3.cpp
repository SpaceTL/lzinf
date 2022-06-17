#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 1600
/*функция для избавления от запятой*/
char* strsep(char** sp, const char* sep) {
	char* p, * s;
	if (sp == NULL || *sp == NULL || **sp == '\0') return NULL;
	s = *sp;
	p = s + strcspn(s, sep);
	if (*p != '\0') *p++ = '\0';
	*sp = p;
	return s;
}
/*структура характеристик*/
struct character {
	char FirstName[20];
	char LastName[20];
	char Gender[20];
	char Occupation[20];
	char Salary[20];
	int sal;
};
struct character ch[N];
/*чтение и запись файла */
void rw() {
	int i = 0, k = 0;
	FILE* in_file;
	in_file = fopen("data.csv", "r");
	FILE* out_file;
	out_file = fopen("result.txt", "w");
	if (in_file == NULL || out_file == NULL)
	{
		printf("Error! Could not open file\n");
		exit(-1);
	}
	char buff[N];
	char* token, * p;
	/*избавление от лишних кавычек и запятых, запись данных в файл
	result.txt*/
	while (fgets(buff, sizeof(buff), in_file)) {
		p = buff;
		token = strsep(&p, ",\n");
		strcpy(ch[i].FirstName, token);
		token = strsep(&p, ",\n");
		strcpy(ch[i].LastName, token);
		token = strsep(&p, ",\n");
		strcpy(ch[i].Gender, token);
		token = strsep(&p, ",\n");
		strcpy(ch[i].Occupation, token);
		token = strsep(&p, ",\n");
		strcpy(ch[i].Salary, token);
		for (int l = 0; l < strlen(ch[i].FirstName); l++) {
			ch[i].FirstName[l] = ch[i].FirstName[l + 1];
			if (ch[i].FirstName[l] == '"')
				ch[i].FirstName[l] = 0;
		}
		for (int l = 0; l < strlen(ch[i].LastName); l++) {
			ch[i].LastName[l] = ch[i].LastName[l + 1];
			if (ch[i].LastName[l] == '"')
				ch[i].LastName[l] = 0;
		}
		for (int l = 0; l < strlen(ch[i].Gender); l++) {
			ch[i].Gender[l] = ch[i].Gender[l + 1];
			if (ch[i].Gender[l] == '"')
				ch[i].Gender[l] = 0;
		}
		for (int l = 0; l < strlen(ch[i].Occupation); l++) {
			ch[i].Occupation[l] = ch[i].Occupation[l + 1];
			if (ch[i].Occupation[l] == '"')
				ch[i].Occupation[l] = 0;
		}
		for (int l = 0; l < strlen(ch[i].Salary); l++) {
			ch[i].Salary[l] = ch[i].Salary[l + 1];
			if (ch[i].Salary[l] == '"')
				ch[i].Salary[l] = 0;
		}
		/*перевод зарплаты из типа char в int*/
		for (int l = 1; l < N; l++) {
			sscanf(ch[l].Salary, "%d", &ch[l].sal);
		}
		fprintf(out_file, "%d %s , %s, %s , %s , %s\n", k,
			ch[i].FirstName, ch[i].LastName, ch[i].Gender,
			ch[i].Occupation, ch[i].Salary);
		i++;
		k++;
	}
	fclose(in_file);
	fclose(out_file);
}
/*сортировка по указанной характеристике*/
void sort() {
	int s;
	char str[20], fn[20], ln[20], gd[20], occ[20];
	int is = 0, salar = 0;
	FILE* fp;
	fp = fopen("sorting.txt", "w");
	scanf("%d", &s);
	while (s > 5 || s < 1) {
		printf("Please, try again\n");
		scanf("%d", &s);
	}
	fprintf(fp, "Result of sorting:\n");
	switch (s) {
	case 1:
		for (int i = 2; i <= N; i++)
			for (int j = 1; j <= N - i; j++)
				if (strcmp(ch[j].FirstName, ch[j + 1].FirstName) > 0) {
					strcpy(str, ch[j].FirstName);
					strcpy(ch[j].FirstName, ch[j + 1].FirstName);
					strcpy(ch[j + 1].FirstName, str);
					strcpy(ln, ch[j].LastName);
					strcpy(ch[j].LastName, ch[j + 1].LastName);
					strcpy(ch[j + 1].LastName, ln);
					strcpy(gd, ch[j].Gender);
					strcpy(ch[j].Gender, ch[j + 1].Gender);
					strcpy(ch[j + 1].Gender, gd);
					strcpy(occ, ch[j].Occupation);
					strcpy(ch[j].Occupation, ch[j + 1].Occupation);
					strcpy(ch[j + 1].Occupation, occ);
					salar = ch[j].sal;
					ch[j].sal = ch[j + 1].sal;
					ch[j + 1].sal = salar;
				}
		for (int i = 0; i < N; i++) {
			fprintf(fp, "%s , %s, %s, %s, %d\n", ch[i].FirstName,
				ch[i].LastName, ch[i].Gender, ch[i].Occupation, ch[i].sal);
		}
		break;
	case 2:
		for (int i = 2; i <= N; i++)
			for (int j = 1; j <= N - i; j++)
				if (strcmp(ch[j].LastName, ch[j + 1].LastName) > 0) {
					strcpy(str, ch[j].LastName);
					strcpy(ch[j].LastName, ch[j + 1].LastName);
					strcpy(ch[j + 1].LastName, str);
					strcpy(fn, ch[j].FirstName);
					strcpy(ch[j].FirstName, ch[j + 1].FirstName);
					strcpy(ch[j + 1].FirstName, fn);
					strcpy(gd, ch[j].Gender);
					strcpy(ch[j].Gender, ch[j + 1].Gender);
					strcpy(ch[j + 1].Gender, gd);
					strcpy(occ, ch[j].Occupation);
					strcpy(ch[j].Occupation, ch[j + 1].Occupation);
					strcpy(ch[j + 1].Occupation, occ);
					salar = ch[j].sal;
					ch[j].sal = ch[j + 1].sal;
					ch[j + 1].sal = salar;
				}
		for (int i = 0; i < N; i++) {
			fprintf(fp, "%s , %s, %s, %s, %d\n", ch[i].LastName,
				ch[i].FirstName, ch[i].Gender, ch[i].Occupation, ch[i].sal);
		}
		break;
	case 3:
		for (int i = 2; i <= N; i++)
			for (int j = 1; j <= N - i; j++)
				if (strcmp(ch[j].Gender, ch[j + 1].Gender) > 0) {
					strcpy(str, ch[j].Gender);
					strcpy(ch[j].Gender, ch[j + 1].Gender);
					strcpy(ch[j + 1].Gender, str);
					strcpy(fn, ch[j].FirstName);
					strcpy(ch[j].FirstName, ch[j + 1].FirstName);
					strcpy(ch[j + 1].FirstName, fn);
					strcpy(ln, ch[j].LastName);
					strcpy(ch[j].LastName, ch[j + 1].LastName);
					strcpy(ch[j + 1].LastName, ln);
					strcpy(occ, ch[j].Occupation);
					strcpy(ch[j].Occupation, ch[j + 1].Occupation);
					strcpy(ch[j + 1].Occupation, occ);
					salar = ch[j].sal;
					ch[j].sal = ch[j + 1].sal;
					ch[j + 1].sal = salar;
				}
		for (int i = 0; i < N; i++) {
			fprintf(fp, "%s , %s, %s, %s, %d\n", ch[i].Gender, ch[i].FirstName,
				ch[i].LastName, ch[i].Occupation, ch[i].sal);
		}
		break;
	case 4:
		for (int i = 2; i <= N; i++)
			for (int j = 1; j <= N - i; j++)
				if (strcmp(ch[j].Occupation, ch[j + 1].Occupation) > 0) {
					strcpy(str, ch[j].Occupation);
					strcpy(ch[j].Occupation, ch[j + 1].Occupation);
					strcpy(ch[j + 1].Occupation, str);
					strcpy(fn, ch[j].FirstName);
					strcpy(ch[j].FirstName, ch[j + 1].FirstName);
					strcpy(ch[j + 1].FirstName, fn);
					strcpy(ln, ch[j].LastName);
					strcpy(ch[j].LastName, ch[j + 1].LastName);
					strcpy(ch[j + 1].LastName, ln);
					strcpy(gd, ch[j].Gender);
					strcpy(ch[j].Gender, ch[j + 1].Gender);
					strcpy(ch[j + 1].Gender, gd);
					strcpy(occ, ch[j].Occupation);
					strcpy(ch[j].Occupation, ch[j + 1].Occupation);
					strcpy(ch[j + 1].Occupation, occ);
					salar = ch[j].sal;
					ch[j].sal = ch[j + 1].sal;
					ch[j + 1].sal = salar;
				}
		for (int i = 0; i < N; i++) {
			fprintf(fp, "%s , %s, %s, %s, %d\n", ch[i].Occupation,
				ch[i].FirstName, ch[i].LastName, ch[i].Gender, ch[i].sal);
		}
		break;
	case 5:
		for (int i = 2; i <= N; i++)
			for (int j = 1; j <= N - i; j++)
				if (ch[j].sal > ch[j + 1].sal) {
					is = ch[j].sal;
					ch[j].sal = ch[j + 1].sal;
					ch[j + 1].sal = is;
					strcpy(fn, ch[j].FirstName);
					strcpy(ch[j].FirstName, ch[j + 1].FirstName);
					strcpy(ch[j + 1].FirstName, fn);
					strcpy(ln, ch[j].LastName);
					strcpy(ch[j].LastName, ch[j + 1].LastName);
					strcpy(ch[j + 1].LastName, ln);
					strcpy(gd, ch[j].Gender);
					strcpy(ch[j].Gender, ch[j + 1].Gender);
					strcpy(ch[j + 1].Gender, gd);
					strcpy(occ, ch[j].Occupation);
					strcpy(ch[j].Occupation, ch[j + 1].Occupation);
					strcpy(ch[j + 1].Occupation, occ);
				}
		for (int i = 0; i < N; i++) {
			fprintf(fp, "%d, %s , %s, %s, %s\n", ch[i].sal, ch[i].FirstName,
				ch[i].LastName, ch[i].Gender, ch[i].Occupation);
		}
		break;
	}
	fclose(fp);
};
int main(void) {
	rw();
	printf("Please, write number of character you want to sort:\n");
	printf("1-FirstName\n2-LastName\n3-Gender\n4-Occupation\n5-Salary\n"
	);
	sort();
	printf("Watch file sorting.txt to look for result of sorting");
	printf("\nSee you!\n");
	return 0;
}