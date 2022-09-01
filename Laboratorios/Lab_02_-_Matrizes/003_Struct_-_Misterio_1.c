#include <stdio.h>
#include <string.h>

typedef double nota;

typedef struct _avaliacoes {
	nota p1, p2, trab;
} avaliacoes;

typedef struct _aluno {
	int ra;
	avaliacoes notas;
	nota media;
	char nome[50];
} aluno;

typedef struct _disciplina {
	int codigo, qtdAlunos;
	nota media;
} disciplina;

void misterio1(aluno fichas[], int qtde) {
	int i, j;
	aluno troca;
	for (i = qtde; i > 0; i--)
		for (j = 0; j < i - 1; j++)
			if ((strcmp(fichas[j].nome, fichas[j+1].nome) > 0)) {
				troca = fichas[j];
				fichas[j] = fichas[j + 1];
				fichas[j + 1] = troca;
			}
}

int main(void) {
	disciplina disciplina1;
	aluno aluno1, aluno2, aluno3;
	strcpy(aluno1.nome, "Emanoel");
	strcpy(aluno2.nome, "Alice");
	strcpy(aluno3.nome, "Tiago");
	disciplina1.qtdAlunos = 3;
	aluno fichas[] = {aluno1, aluno2, aluno3};
	misterio1(fichas, disciplina1.qtdAlunos);
	for (int i = 0; i < disciplina1.qtdAlunos; i++)
		printf("%s\n", fichas[i].nome);
	return 0;
}
