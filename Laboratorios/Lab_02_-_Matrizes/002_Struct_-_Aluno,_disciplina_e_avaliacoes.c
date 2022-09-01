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
	int codigo, qntAlunos;
	nota media;
} disciplina;

int main(void) {
	disciplina disciplina1;
	aluno aluno1, aluno2, aluno3;
	aluno1.media = 6;
	aluno2.media = 8;
	aluno3.media = 10;
	disciplina1.qntAlunos = 3;
	disciplina1.media = (aluno1.media + aluno2.media + aluno3.media) / disciplina1.qntAlunos;
	printf("%g", disciplina1.media);
	return 0;
}
