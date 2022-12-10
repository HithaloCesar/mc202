#include <stdlib.h>
#include <string.h>
#include "hash.h"

/**
 * @brief Informa se um número é primo ou não.
 * @param n Número a ser analisado.
 * @return Caso o número seja primo, retorna 1. Caso contrário, retorna 0.
*/
int prime(int n) {
	if (n <= 1)
		return 0;
	int divisor = 2;
	while (divisor * divisor <= n) {
		if (n % divisor == 0)
			return 0;
		divisor++;
	}
	return 1;
}

/**
 * @brief Informa o menor número primo maior que n.
 * @param n Número cujo próximo número primo deve ser encontrado.
 * @return Número primo encontrado.
*/
int prime_next(int n) {
	n++;
	while (!prime(n))
		n++;
	return n;
}

/**
 * @brief Cria uma tabela hash de processos.
 * @param m Tamanho da tabela hash.
 * @return Endereço da tabela hash criada.
*/
p_lawsuit_hashtable lawsuit_hashtable_create(int m) {
	p_lawsuit_hashtable ht = malloc(sizeof(lawsuit_hashtable));
	ht->data = malloc(m * sizeof(p_lawsuit));
	for (int ht_idx = 0; ht_idx < m; ht_idx++)
		ht->data[ht_idx] = NULL;
	ht->n = 0;
	ht->m = m;
	return ht;
}

/**
 * @brief Função hash, responsável por calcular o índice de acordo com a chave.
 * @param ht Tabela hash de processos.
 * @param id ID do processo, utilizado como chave na função hash.
 * @return Índice calculado pela função hash.
*/
int lawsuit_hashtable_hash(p_lawsuit_hashtable ht, int id) {
	int p = prime_next(ht->m);
	int a = ht->m - (ht->m / 2);
	int b = ht->m - (ht->m / 3);
	int k = id / 1000;
	return ((a * k + b) % p) % ht->m;
}

/**
 * @brief Cria um processo.
 * @param id ID do processo.
 * @param name Nome do processo.
 * @param time Tempo de espera para o processo ser atendido, em dias.
 * @return Endereço do processo criado.
*/
p_lawsuit lawsuit_create(int id, char *name, int time) {
	p_lawsuit ls = malloc(sizeof(lawsuit));
	ls->id = id;
	strcpy(ls->name, name);
	ls->time = time;
	ls->deleted = 0;
	return ls;
}

/**
 * @brief Insere um processo na tabela hash de processos.
 * @param ht Tabela hash de processos no qual o processo será inserido.
 * @param id ID do processo a ser inserido.
 * @param name Nome do processo a ser inserido.
 * @param time Tempo de espera para o processo ser atendido, em dias.
 * @return Índice do processo na tabela hash.
*/
int lawsuit_insert(p_lawsuit_hashtable ht, int id, char *name, int time) {
	if (ht->n > ht->m / 2)
		ht = lawsuit_hahstable_resize(ht);
	int ht_idx = lawsuit_hashtable_hash(ht, id);
	while (ht->data[ht_idx] != NULL && !ht->data[ht_idx]->deleted) {
		if (ht->data[ht_idx]->id == id) {
			ht->n--;
			break;
		}
		ht_idx = (ht_idx + 1) % ht->m;
	}
	if (ht->data[ht_idx] != NULL)
		free(ht->data[ht_idx]);
	ht->data[ht_idx] = lawsuit_create(id, name, time);
	ht->n++;
	return ht_idx;
}

/**
 * @brief Redimensiona uma tabela hash de processos.
 * @param ht Tabela hash de processos a ser redimensionada.
 * @return Tabela hash de processos já redimensionada.
*/
p_lawsuit_hashtable lawsuit_hahstable_resize(p_lawsuit_hashtable ht) {
	int m_new = prime_next(2 * ht->m);
	p_lawsuit *ht_data_old = ht->data;
	ht->data = malloc(m_new * sizeof(p_lawsuit));
	for (int i = 0; i < m_new; i++)
		ht->data[i] = NULL;
	int m_old = ht->m;
	ht->m = m_new;
	ht->n = 0;
	for (int ht_idx = 0; ht_idx < m_old; ht_idx++)
		if (ht_data_old[ht_idx] != NULL && !ht_data_old[ht_idx]->deleted)
			lawsuit_insert(ht, ht_data_old[ht_idx]->id, ht_data_old[ht_idx]->name, ht_data_old[ht_idx]->time);
	for (int i = 0; i < m_old; i++)
		if (ht_data_old[i] != NULL)
			free(ht_data_old[i]);
	free(ht_data_old);
	return ht;
}

/**
 * @brief Procura por um processo na tabela hash.
 * @param ht Tabela hash de processos.
 * @param id ID do processo a ser procurado.
 * @return Caso o processo seja encontrado, retona seu índice na tabela hash.
 *         Caso contrário, retorna -1.
*/
int lawsuit_search(p_lawsuit_hashtable ht, int id) {
	int n = lawsuit_hashtable_hash(ht, id);
	int n_ini = n;
	while (ht->data[n] != NULL) {
		if (!ht->data[n]->deleted && ht->data[n]->id == id)
			return n;
		n = (n + 1) % ht->m;
		if (n == n_ini)
			return -1;
	}
	return -1;
}

/**
 * @brief Remove um processo da tabela hash.
 * @param ht Tabela hash de processos.
 * @param id ID do processo a ser removido.
 * @return Caso o processo seja removido com sucesso, retorna 0. Caso o
 *         processo não seja encontrado, retorna -1.
*/
int lawsuit_del(p_lawsuit_hashtable ht, int id) {
	int idx = lawsuit_search(ht, id);
	if (idx == -1)
		return -1;
	ht->data[idx]->deleted = 1;
	ht->n--;
	return 0;
}

/**
 * @brief Libera da memória uma tabela hash de processos.
 * @param ht Tabela hash de processos a ser liberada da memória.
*/
void lawsuit_hashtable_free(p_lawsuit_hashtable ht) {
	for (int i = 0; i < ht->m; i++)
		if (ht->data[i] != NULL)
			free(ht->data[i]);
	free(ht->data);
	free(ht);
}
