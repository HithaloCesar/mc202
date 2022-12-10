#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobra.h"

/** @brief Aloca uma matriz de caracteres.
 *  @param rows_alloc Quantidade de linhas a serem alocadas na matriz.
 *  @param cols_alloc Quantidade de colunas a serem alocadas na matriz.
 *  @return A matriz de caracteres alocada.
 */
p_matrix_char matrix_char_alloc(int rows_alloc, int cols_alloc) {
	p_matrix_char matrix = malloc(sizeof(struct matrix_char));
	matrix->data = malloc(rows_alloc * sizeof(char *));
	for (int row_idx = 0; row_idx < rows_alloc; row_idx++)
		matrix->data[row_idx] = malloc(cols_alloc * sizeof(char));
	return matrix;
}

/** @brief Cria uma nova matriz de caracteres, ou seja, aloca-a na memória e
 *         define a contagem de linhas e colunas para zero.
 *  @param rows_alloc Quantidade de linhas a serem alocadas na matriz.
 *  @param cols_alloc Quantidade de colunas a serem alocadas na matriz.
 *  @return A matriz de caracteres criada.
 */
p_matrix_char matrix_char_create(int rows_alloc, int cols_alloc) {
	p_matrix_char matrix = matrix_char_alloc(rows_alloc, cols_alloc);
	matrix->rows_alloc = rows_alloc;
	matrix->cols_alloc = cols_alloc;
	matrix->row_cnt = 0;
	matrix->col_cnt = 0;
	return matrix;
}

/** @brief Preenche completamente uma matriz de caracteres com um caractere e
 *         altera as dimensões para compreender todo o espaço alocado.
 *  @param matrix Matriz a ser preenchida.
 *  @param c Caractere a ser inserido em todas as entradas da matriz.
 */
void matrix_char_fill(p_matrix_char matrix, char c) {
	for (int row_idx = 0; row_idx < matrix->rows_alloc; row_idx++)
		for (int col_idx = 0; col_idx < matrix->cols_alloc; col_idx++)
			matrix->data[row_idx][col_idx] = c;
	matrix->row_cnt = matrix->rows_alloc;
	matrix->col_cnt = matrix->cols_alloc;
}

/** @brief Permite a inserção de uma fruta no mapa do jogo snake.
 *  @param command String que deve receber "FRUTA" para o sucesso da função.
 *  @param fruit Coordenadas da fruta no mapa.
 *  @param map Matriz de caracteres que representa o mapa do jogo snake.
 */
void fruit_insert(char *command, p_coords_2d fruit, p_matrix_char map) {
	scanf("%s", command);
	if (strcmp(command, "FRUTA") != 0)
		exit(1);
	scanf("%d %d", &fruit->row, &fruit->col);
	map->data[fruit->row][fruit->col] = '*';
}

/** @brief Permite a inserção da cobra no mapa do jogo snake.
 *  @param command String que deve receber "COBRA" para o sucesso da função.
 *  @param map Matriz de caracteres que representa o mapa do jogo snake.
 *  @return Lista duplamente ligada que representa a cobra.
 */
p_dll_coords_2d snake_insert(char *command, p_matrix_char map) {
	if (strcmp(command, "COBRA") != 0)
		exit(1);
	int snake_head_row, snake_head_col;
	scanf("%d %d ", &snake_head_row, &snake_head_col);
	p_dll_coords_2d snake = dll_coords_2d_create(snake_head_row, snake_head_col);
	map->data[snake->first->coords->row][snake->first->coords->col] = '#';
	return snake;
}

/** @brief Aloca um nó de uma lista duplamente ligada com coordenadas 2D.
 *  @return Nó alocado.
 */
p_dll_coords_2d_node dll_coords_2d_alloc(void) {
	p_dll_coords_2d_node node = malloc(sizeof(struct dll_coords_2d_node));
	node->coords = malloc(sizeof(struct coords_2d));
	return node;
}

/** @brief Cria um nó de uma lista duplamente ligada com coordendas 2D.
 *  @param row Linha do ponto.
 *  @param col Coluna do ponto.
 *  @return Nó alocado.
 */
p_dll_coords_2d_node dll_coords_2d_node_create(int row, int col) {
	p_dll_coords_2d_node first_node = dll_coords_2d_alloc();
	first_node->coords->row = row;
	first_node->coords->col = col;
	first_node->next = NULL;
	first_node->prev = NULL;
	return first_node;
}

/** @brief Cria uma lista duplamente ligada com coordenadas 2D.
 *  @param row Linha do ponto do primeiro nó.
 *  @param col Coluna do ponto do primeiro nó.
 *  @return Lista duplamente ligada criada.
 */
p_dll_coords_2d dll_coords_2d_create(int row, int col) {
	p_dll_coords_2d list = malloc(sizeof(struct dll_coords_2d));
	list->first = dll_coords_2d_node_create(row, col);
	list->last = list->first;
	list->len = 1;
	return list;
}

/** @brief Imprime uma matriz de caracteres.
 *  @param matrix Matriz a ser impressa.
 */
void matrix_char_print(p_matrix_char matrix) {
	for (int row_idx = 0; row_idx < matrix->row_cnt; row_idx++) {
		for (int col_idx = 0; col_idx < matrix->col_cnt; col_idx++)
			printf("%c ", matrix->data[row_idx][col_idx]);
		printf("\n");
	}
}

/** @brief Calcula o resto truncado da divisão entre dois inteiros.
 *  @param a Dividendo.
 *  @param b Divisor.
 *  @return Resto truncado da divisão entre a e b.
 */
int modulo_floored(int a, int b) {
	return ((a % b) + b) % b;
}

/** @brief Caso necessário, conserta o índex de um vetor. Índices negativos
 *         percorrem o vetor da direita para a esquerda. Índices maiores que o
 *         tamanho do vetor percorrem o vetor da esquerda para a direita
 *         novamente.
 *  @param out_of_bounds_idx Índice a ser consertado.
 *  @param array_len Quantidade de elementos no vetor.
 *  @return Índice consertado.
 */
int array_idx_fix(int out_of_bounds_idx, int array_len) {
	return modulo_floored(out_of_bounds_idx, array_len);
}

/** @brief Lê um caractere que referencia a direção da movimentação e define as
 *         coordenadas do destino da cabeça da cobra.
 *  @param dest Coordenadas 2D do destino da cabeça da cobra.
 *  @param snake Cobra, representada por uma lista duplamente ligada com
 *               coordenadas 2D.
 *  @param map Matriz de caracteres que representa o mapa do jogo snake.
 */
void dest_coords_set(
		p_coords_2d dest,
		p_dll_coords_2d snake,
		p_matrix_char map) {
	char move;
	scanf(" %c", &move);
	switch (move) {
		case 'w':
			dest->row = array_idx_fix(snake->first->coords->row - 1, map->row_cnt);
			dest->col = snake->first->coords->col;
			break;
		case 'a':
			dest->row = snake->first->coords->row;
			dest->col = array_idx_fix(snake->first->coords->col - 1, map->col_cnt);
			break;
		case 's':
			dest->row = array_idx_fix(snake->first->coords->row + 1, map->row_cnt);
			dest->col = snake->first->coords->col;
			break;
		case 'd':
			dest->row = snake->first->coords->row;
			dest->col = array_idx_fix(snake->first->coords->col + 1, map->col_cnt);
			break;
		default:
			exit(1);
			break;
	}
}

/** @brief Troca as posições do primeiro e do último nó de uma lista duplamente
 *         ligada com coordenadas 2D.
 *  @param list Lista duplamente ligada cujo primeiro e último nó terão suas
 *              posições trocadas.
 */
void dll_coords_2d_swap_first_last(p_dll_coords_2d list) {
	if (list->first == NULL || list->first->next == NULL)
		return;
	p_dll_coords_2d_node new_last_node = list->last->prev;
	new_last_node->next = NULL;
	list->last->prev = NULL;
	list->last->next = list->first;
	list->first->prev = list->last;
	list->first = list->last;
	list->last = new_last_node;
}

/** @brief Executa o movimento da cobra no jogo snake.
 *  @param snake Cobra, representada por uma lista duplamente ligada com
 *               coordenadas 2D.
 *  @param dest Coordenadas 2D do destino da cabeça da cobra.
 *  @param map Matriz de caracteres que representa o mapa do jogo snake.
 */
void snake_move(p_dll_coords_2d snake, p_coords_2d dest, p_matrix_char map) {
	map->data[snake->last->coords->row][snake->last->coords->col] = '_';
	dll_coords_2d_swap_first_last(snake);
	snake->first->coords->row = dest->row;
	snake->first->coords->col = dest->col;
	map->data[snake->first->coords->row][snake->first->coords->col] = '#';
}

/** @brief Insere um nó na frente de outro nó em uma lista duplamente ligada
 *         com coordenadas 2D.
 *  @param list Lista duplamente ligada na qual um novo nó será inserido.
 *  @param node Nó referência para a inserção do novo nó.
 *  @param row Linha do ponto do novo nó.
 *  @param col Coluna do ponto do novo nó.
 */
void dll_coords_2d_insert_before(
		p_dll_coords_2d list,
		p_dll_coords_2d_node node,
		int row,
		int col) {
	p_dll_coords_2d_node new_node = dll_coords_2d_alloc();
	new_node->next = node;
	if (node->prev == NULL) {
		new_node->prev = NULL;
		list->first = new_node;
	} else {
		new_node->prev = node->prev;
		node->prev->next = new_node;
	}
	node->prev = new_node;
	new_node->coords->row = row;
	new_node->coords->col = col;
	list->len++;
}

/** @brief Aumenta o tamanho da cobra no jogo snake.
 *  @param snake Cobra, representada por uma lista duplamente ligada com
 *               coordenadas 2D.
 *  @param dest Coordenadas 2D do destino da cabeça da cobra.
 *  @param map Matriz de caracteres que representa o mapa do jogo snake.
 */
void snake_eat(p_dll_coords_2d snake, p_coords_2d dest, p_matrix_char map) {
	dll_coords_2d_insert_before(snake, snake->first, dest->row, dest->col);
	map->data[snake->first->coords->row][snake->first->coords->col] = '#';
}

/** @brief Libera da memória uma matriz de caracteres.
 *  @param matrix Matriz de caracteres a ser liberada.
 */
void matrix_char_free(p_matrix_char matrix) {
	for (int row_idx = 0; row_idx < matrix->rows_alloc; row_idx++)
		free(matrix->data[row_idx]);
	free(matrix->data);
	free(matrix);
}

/** @brief Libera recursivamente da memória os nós de uma lista duplamente
 *         ligada com coordenadas 2D.
 *  @param node Primeiro nó da lista duplamente ligada.
 */
static void dll_coords_2d_free_node(p_dll_coords_2d_node node) {
	if (node != NULL) {
		dll_coords_2d_free_node(node->next);
		free(node->coords);
		free(node);
	}
}

/** @brief Libera da memória os nós de uma lista duplamente ligada com
 *         coordenadas 2D e a lista em si.
 *  @param list Lista duplamente ligada.
 */
void dll_coords_2d_free(p_dll_coords_2d list) {
	dll_coords_2d_free_node(list->first);
	free(list);
}
