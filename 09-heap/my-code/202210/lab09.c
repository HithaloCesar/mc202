#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/**
 * @brief Executa o código principal, responsável por gerenciar uma fila de
 *        prioridade de processos criminais.
 * @return Caso o programa seja executado com sucesso, retorna 0.
*/
int main(void) {
	int lawsuit_cnt;
	scanf("%d", &lawsuit_cnt);
	p_lawsuit_heap heap = lawsuit_heap_create(lawsuit_cnt);
	for (int i = 0; i < lawsuit_cnt; i++) {
		int P, C;
		scanf("%d %d", &P, &C);
		lawsuit_heap_insert(heap, P, C);
	}
	int command_cnt;
	scanf("%d", &command_cnt);
	for (int i = 0; i < command_cnt; i++) {
		char command;
		int remove_cnt, P, C;
		scanf(" %c", &command);
		switch (command) {
			case 'R':
				scanf("%d", &remove_cnt);
				printf("PROCESSOS REMOVIDOS: ");
				for (int j = 0; j < remove_cnt - 1; j++)
					printf("%d ", lawsuit_heap_extract(heap).P);
				printf("%d", lawsuit_heap_extract(heap).P);
				printf("\n");
				break;
			case 'M':
				scanf("%d %d", &P, &C);
				lawsuit_heap_priority_change(heap, P, C);
				break;
		}
	}
	printf("FINALIZADO!\n");
	free(heap->data);
	free(heap);
	return 0;
}
