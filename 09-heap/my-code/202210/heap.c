#include <stdlib.h>
#include "heap.h"

#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)

/**
 * @brief Troca o endereço entre dois processos.
 * @param a Processo a ser trocado de endereço.
 * @param b Outro processo a ser trocado de endereço.
*/
void lawsuit_heap_switch(lawsuit *a, lawsuit *b) {
	lawsuit t = *a;
	*a = *b;
	*b = t;
}

/**
 * @brief Cria uma fila de prioridade de processos.
 * @param alloc Quantidade máxima de processos que caberão na fila.
 * @return Fila de prioridade de processos criada.
*/
p_lawsuit_heap lawsuit_heap_create(int alloc) {
	p_lawsuit_heap heap = malloc(alloc * sizeof(lawsuit_heap));
	heap->data = malloc(alloc * sizeof(lawsuit));
	heap->alloc = alloc;
	heap->cnt = 0;
	return heap;
}

/**
 * @brief Reduz o índice de um processo para restaurar a fila de prioridade.
 * @param heap Fila de prioridade de processos.
 * @param i Índice do processo a ser elevado na fila de prioridade.
*/
void lawsuit_heapify_up(p_lawsuit_heap heap, int i) {
	if (i == 0 || heap->data[PARENT(i)].C < heap->data[i].C)
		return;
	// int parent_C_is_bigger = heap->data[PARENT(i)].C > heap->data[i].C;
	if (
			heap->data[PARENT(i)].C > heap->data[i].C
			|| heap->data[PARENT(i)].P < heap->data[i].P) {
		lawsuit_heap_switch(&heap->data[i], &heap->data[PARENT(i)]);
		lawsuit_heapify_up(heap, PARENT(i));
	}
}

/**
 * @brief Insere um novo processo numa fila de prioridade.
 * @param heap Fila de prioridade de processos.
 * @param P Número identificador do processo.
 * @param C Código de prioridade do processo.
*/
void lawsuit_heap_insert(p_lawsuit_heap heap, int P, int C) {
	heap->data[heap->cnt].P = P;
	heap->data[heap->cnt].C = C;
	heap->cnt++;
	lawsuit_heapify_up(heap, heap->cnt - 1);
}

/**
 * @brief Aumenta o índice de um processo para restaurar a fila de prioridade.
 * @param heap Fila de prioridade de processos.
 * @param i Índice do processo a ser rebaixado na fila de prioridade.
*/
void lawsuit_heapify_down(p_lawsuit_heap heap, int i) {
	if (LEFT(i) >= heap->cnt)
		return;
	int highest = LEFT(i);
	if (RIGHT(i) < heap->cnt) {
		if (heap->data[RIGHT(i)].C > heap->data[LEFT(i)].C) {}
		else if (
				heap->data[RIGHT(i)].C < heap->data[LEFT(i)].C
				|| heap->data[RIGHT(i)].P > heap->data[LEFT(i)].P)
			highest = RIGHT(i);
	}
	if (heap->data[i].C < heap->data[highest].C) {}
	else if (
			heap->data[i].C > heap->data[highest].C
			|| heap->data[i].P < heap->data[highest].P) {
		lawsuit_heap_switch(&heap->data[i], &heap->data[highest]);
		lawsuit_heapify_down(heap, highest);
	}
}

/**
 * @brief Extrai o processo de mais alta prioridade da fila.
 * @param heap Fila de prioridade de processos.
 * @return Processo de mais alta prioridade da fila.
*/
lawsuit lawsuit_heap_extract(p_lawsuit_heap heap) {
	lawsuit item = heap->data[0];
	lawsuit_heap_switch(&heap->data[0], &heap->data[heap->cnt - 1]);
	heap->cnt--;
	lawsuit_heapify_down(heap, 0);
	return item;
}

/**
 * @brief Procura um processo na fila de prioridades.
 * @param heap Fila de prioridade de processos.
 * @param P Número identificador do processo a ser procurado.
 * @return Índice do processo na fila de prioridade.
*/
int lawsuit_heap_search(p_lawsuit_heap heap, int P) {
	int idx;
	for (idx = 0; heap->data[idx].P != P; idx++) {}
	return idx;
}

/**
 * @brief Altera a prioridade de um processo na fila.
 * @param heap Fila de prioridade de processos.
 * @param P Número identificador do processo cuja prioridade será alterada.
 * @param C Novo código de prioridade do processo.
*/
void lawsuit_heap_priority_change(p_lawsuit_heap heap, int P, int C) {
	int idx = lawsuit_heap_search(heap, P);
	if (C < heap->data[idx].C) {
		heap->data[idx].C = C;
		lawsuit_heapify_up(heap, idx);
	} else {
		heap->data[idx].C = C;
		lawsuit_heapify_down(heap, idx);
	}
}
