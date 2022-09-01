#include <stdio.h>

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

int main(void) {
	disciplina disciplina1;
	aluno aluno1, aluno2, aluno3;
	aluno1.notas.p1 = 1;
	aluno1.notas.p2 = 2;
	aluno1.notas.trab = 6;
	aluno1.media = (aluno1.notas.p1 + aluno1.notas.p2 + aluno1.notas.trab) / 3;
	printf("%g", aluno1.media);
	return 0;
}
