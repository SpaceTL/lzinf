#include<stdio.h>
#include<stdlib.h>
#include <string.h>
/*���� � �������� ������������ ����� char*/
typedef char* VAL; typedef char* KEY;
#define HASHSIZE 21
#define EQKEY(s1, s2) (strcmp(s1, s2) == 0)
#define FREEKEY(s) free(s)
#define FREEVAL(s) free(s)
#define SETVAL(at,s) at = strdup(s)
#define SETKEY(at,s) at = strdup(s)
struct cell { /*��������� ������*/
	struct cell* next;
	KEY key;
	VAL val;
} *hashtable[HASHSIZE];
unsigned int hash;
int HASHFUNC(KEY key) { /* ���-������� */
	unsigned int i = 0; char* keysrc = key;
	while (*key) {
		i = (i << 1) | (i >> 15); /* ��������� ����� ����� */
		i ^= *key++;
	}
	hash = i % HASHSIZE;
	printf("hash(%s)=%d\n", keysrc, hash);
	return hash;
}
struct cell* get(KEY key) { /*��������� �����*/
	struct cell* p;
	for (p = hashtable[HASHFUNC(key)]; p; p = p->next)
		if (EQKEY(p->key, key))
			return p;
	return NULL;
}
void set(KEY key, VAL val) { /*��������� ��������*/
	struct cell* p;
	/* �������� �������� */
	if ((p = get(key)) == NULL) {
		if (!(p = (struct cell*)malloc(sizeof(*p)))) return;
		SETKEY(p->key, key);
		p->next = hashtable[hash]; /* hash ��������� � get() */
		hashtable[hash] = p;
	}
	else /* �������� �������� */
		FREEVAL(p->val);
	SETVAL(p->val, val);
}
int del(KEY key) { /*�������� ��������*/
	int indx = HASHFUNC(key);
	struct cell* p, * prev = NULL;
	if ((p = hashtable[indx]) == NULL) return 0;
	for (; p; prev = p, p = p->next)
		if (EQKEY(p->key, key)) {
			FREEVAL(p->val); FREEKEY(p->key);
			if (p == hashtable[indx])
				hashtable[indx] = p->next;
			else prev->next = p->next;
			free((void*)p); return 1; /* �������� */
		}
	return 0;
}
void printcell(struct cell* ptr) { /*������ ������*/
	putchar('(');
	printf("%s", ptr->key); putchar(',');
	printf("%s", ptr->val); putchar(')');
}
void printtable() {
	register int i; struct cell* p;
	printf("----TABLE CONTENTS----\n");
	for (i = 0; i < HASHSIZE; i++)
		if ((p = hashtable[i]) != NULL) {
			printf("%d: ", i);
			for (; p; p = p->next)
				printcell(p), putchar(' ');
			putchar('\n');
		}
}
struct celliter {
	int index; struct cell* ptr;
};
struct cell* nextpair(struct celliter* ci) {
	struct cell* result;
	while ((result = ci->ptr) == NULL) {
		if (++(ci->index) >= HASHSIZE)
			return NULL; /* ������ ��� */
		ci->ptr = hashtable[ci->index];
	}
	ci->ptr = result->next; return result;
}
struct cell* resetiter(struct celliter* ci) {
	ci->index = (-1); ci->ptr = NULL;
	return nextpair(ci); /* ������ �������� */
}
int main(void) { /* ������� �� ���� � �������� ������ ��������
�������� */
	struct celliter ci; struct cell* cl;
	char key[40], value[40]; struct cell* val;
	extern FILE* popen(); FILE* fp; char* s;
	/* popen() ������ ����� �������, �������� � 1-�� ��������� */
	fp = popen("ls -s", "r");
	while (fscanf(fp, "%s%s", value, key) == 2)
		set(key, value);
	pclose(fp);
	for (;;) {
		printf("-> ");
		if (!fgets(key, 126, fp)) break; /* EOF */
		if (*key == '-') { /* -���� :������� */
			printf(del(key + 1) ? "OK\n" : "no such key\n");
			continue;
		}
		if (!*key || !strcmp(key, "=")) { /* = :����������� �������*/
			printtable(); continue;
		}
		if ((s = strchr(key, '='))) { /* ����=�������� :�������� */
			*s++ = '\0';
			set(key, s); continue;
		}
		if ((val = get(key)) == NULL) /* ���� :����� �������� */
			printf("There's no such key\n");
		else {
			printf("Value "); printf("%s", val->val);
			putchar('\n');
		}
	}
	/* ���������� ������� ��� ������ ��������� */
	for (cl = resetiter(&ci); cl; cl = nextpair(&ci))
		printcell(cl), putchar('\n');
	printtable();
	return 0;
}