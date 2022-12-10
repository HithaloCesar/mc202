#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayInt *pArrayInt;

/** @struct Array lab04.c lab04.c
 *  @brief Representa um vetor de inteiros.
 *  @tparam data Números presentes no vetor.
 *  @tparam len Quantidade de números presentes no vetor.
 *  @tparam alloc Capacidade do vetor.
 */
struct ArrayInt {
	int *data;
	int len;
	int alloc;
};

/** @brief Cria um vetor de inteiros.
 *  @param len Quantidade de números presentes no vetor.
 *  @return Um ponteiro para o vetor de inteiros criado.
 */
pArrayInt array_int_create(int len) {
	pArrayInt array = malloc(sizeof(struct ArrayInt));
	array->data = malloc(len * sizeof(int));
	array->len = 0;
	array->alloc = len;
	return array;
}

/** @brief Adiciona um inteiro em um vetor de inteiros.
 *  @param array Vetor no qual o número deve ser adicionado.
 *  @param add Inteiro a ser adicionado no vetor.
 */
void array_int_add(pArrayInt array, int add) {
	if (array->len == array->alloc) {
		array->alloc *= 2;
		array->data = realloc(array->data, array->alloc * sizeof(int));
	}
	array->data[array->len] = add;
	array->len++;
}

/** @brief Permite a inserção de inteiros em um vetor.
 *  @param array Vetor de inteiros a ser preenchido.
 *  @param array_len Quantidade de inteiros a serem inseridos no vetor.
 */
void array_int_set(pArrayInt array, int array_len) {
	array->len = 0;
	for (int int_idx = 0; int_idx < array_len; int_idx++) {
		int integer;
		scanf("%d", &integer);
		array_int_add(array, integer);
	}
}

/** @brief Encontra os limites do subvetor de maior soma em um vetor de int.
 *  @param array Vetor onde a busca pelo subvetor de maior soma deve ser feita.
 *  @param max_left Limite esquerdo do subvetor de maior soma.
 *  @param max_right Limite direito do subvetor de maior soma.
 */
void array_max_sum(pArrayInt array, int *max_left, int *max_right) {
	int sum = 0, max_sum = 0;
	int left = 0;
	int right = 0;
	int neg_sum = 0;
	*max_left = 0;
	*max_right = 0;
	for (int array_idx = 0; array_idx < array->len; array_idx++) {
		if (array->data[array_idx] >= 0) {
			if (array_idx == 0 || array->data[array_idx - 1] < 0) {
				if (sum + neg_sum >= 0)
					sum += neg_sum;
				else {
					sum = 0;
					left = array_idx;
				}
			}
			sum += array->data[array_idx];
			right = array_idx;
			neg_sum = 0;
		} else {
			if (array_idx == 0) {
				sum = array->data[array_idx];
				max_sum = sum;
			}
			if (array->data[array_idx] > max_sum) {
				sum = array->data[array_idx];
				left = array_idx;
				right = array_idx;
			}
			neg_sum += array->data[array_idx];
		}
		if (sum > max_sum) {
			max_sum = sum;
			*max_left = left;
			*max_right = right;
		}
	}
}

/** @brief Libera da memória um vetor de inteiros.
 *  @param array Vetor a ser liberado da memória.
 */
void array_int_free(pArrayInt array) {
	free(array->data);
	free(array);
}

/** @brief Calcula a média de inteiros.
 *  @param array Inteiros cuja média deve ser calculada.
 *  @return A média truncada.
 */
int array_int_avg_trunc(pArrayInt array) {
	int sum = 0;
	for (int i = 0; i < array->len; i++)
		sum += array->data[i];
	int average = sum / array->len;
	return average;
}

/** @brief Copia um vetor de inteiros.
 *  @param array Inteiros a serem copiados.
 *  @return Um ponteiro para a cópia do vetor de inteiros.
 */
pArrayInt array_int_copy(pArrayInt array) {
	pArrayInt copy = array_int_create(array->len);
	for (int i = 0; i < array->len; i++)
		array_int_add(copy, array->data[i]);
	return copy;
}

/** @brief Normaliza um vetor de inteiros pela média.
 *  @param array Vetor a ser normalizado pela média.
 *  @return Um ponteiro para o vetor já normalizado pela média.
 */
pArrayInt array_int_normalize(pArrayInt array) {
	int avg = array_int_avg_trunc(array);
	pArrayInt result = array_int_copy(array);
	for (int i = 0; i < array->len; i++)
		result->data[i] -= avg;
	return result;
}

/** @brief Executa o programa principal, responsável por imprimir um relatório
 *         da situação de tropas de batalha.
 *  @return Caso o programa seja executado com sucesso, retorna 0.
 */
int main(void) {
	int troops_cnt;
	scanf("%d", &troops_cnt);
	pArrayInt troop = array_int_create(64);
	pArrayInt elite_troop = array_int_create(64);
	for (int troop_idx = 0; troop_idx < troops_cnt; troop_idx++) {
		int troop_len;
		scanf("%d", &troop_len);
		array_int_set(troop, troop_len);
		int left = 0, right = 0;
		array_max_sum(troop, &left, &right);
		printf("Sub-tropa Forte %d: ", troop_idx + 1);
		for (int soldier_idx = left; soldier_idx < right + 1; soldier_idx++) {
			printf("%d ", troop->data[soldier_idx]);
			array_int_add(elite_troop, troop->data[soldier_idx]);
		}
		printf("\n");
		troop->len = 0;
	}
	array_int_free(troop);
	printf("Sub-tropa Elite: ");
	pArrayInt elite_troop_normalized = array_int_normalize(elite_troop);
	int left = 0, right = 0;
	array_max_sum(elite_troop_normalized, &left, &right);
	for (int soldier_idx = left; soldier_idx < right + 1; soldier_idx++)
		printf("%d ", elite_troop->data[soldier_idx]);
	printf("\n");
	array_int_free(elite_troop);
	array_int_free(elite_troop_normalized);
	return 0;
}
