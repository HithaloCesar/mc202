#include <stdio.h>
#include "hash.h"

/**
 * @brief Executa o código principal, responsável por gerenciar uma tabela hash
 *        de processos criminais.
 * @return Caso o programa seja executado com sucesso, retorna 0.
*/
int main(void) {
	int operation_cnt;
	scanf("%d", &operation_cnt);
	p_lawsuit_hashtable ht = lawsuit_hashtable_create(prime_next(50));
	for (int i = 0; i < operation_cnt; i++) {
		char operation;
		scanf(" %c", &operation);
		int id, time, idx;
		char name[32];
		scanf("%d", &id);
		switch (operation) {
			case 'I':
				scanf("%s", name);
				scanf("%d", &time);
				lawsuit_insert(ht, id, name, time);
				printf("PROCESSO %d INSERIDO!\n", id);
				break;
			case 'R':
				lawsuit_del(ht, id);
				printf("PROCESSO %d REMOVIDO!\n", id);
				break;
			case 'C':
				idx = lawsuit_search(ht, id);
				if (idx == -1)
					printf("PROCESSO %d NAO ENCONTRADO!\n", id);
				else
					printf("PROCESSO %d: %s\n", ht->data[idx]->id, ht->data[idx]->name);
				break;
			case 'T':
				idx = lawsuit_search(ht, id);
				printf("TEMPO DO PROCESSO %d: %d DIAS.\n", ht->data[idx]->id, ht->data[idx]->time);
				break;
		}
	}
	printf("FINALIZADO!");
	lawsuit_hashtable_free(ht);
	return 0;
}
