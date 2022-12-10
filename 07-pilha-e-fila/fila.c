#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

/**
 * @brief Gera um buffer circular de caracteres.
 * @return Buffer circular de caracteres gerado.
*/
p_buf_char_circ buf_char_circ_create(void) {
	p_buf_char_circ buffer = malloc(sizeof(struct buf_char_circ));
	buffer->ini = 0;
	buffer->end = 0;
	buffer->len = 0;
	return buffer;
}

/**
 * @brief Insere uma string no buffer.
 * @param buffer Buffer circular de caracteres que receberá a string.
 * @param string String a ser copiada para o buffer.
*/
void buffer_circ_str_insert(p_buf_char_circ buffer, char* string) {
	for (int i = 0; string[i] != '\0'; i++) {
		buffer->data[buffer->end] = string[i];
		buffer->end = (buffer->end + 1) % BUF_CHAR_ALLOC;
		buffer->len++;
	}
}

/**
 * @brief Ejeta um caractere de um buffer circular de caracteres.
 * @param buffer Buffer circular de caracteres em que haverá a expulsão de um
 *               caractere.
 * @return Caractere removido do buffer circular de caracteres.
*/
char buf_char_circ_pop(p_buf_char_circ buffer) {
	char c = buffer->data[buffer->ini];
	buffer->ini = (buffer->ini + 1) % BUF_CHAR_ALLOC;
	buffer->len--;
	return c;
}

/**
 * @brief Imprime na tela o conteúdo de um buffer circular de caracteres.
 * @param buffer Buffer circular de caracteres a ser impresso na tela.
*/
void buf_char_circ_print(p_buf_char_circ buffer) {
	for (int i = 0; i < buffer->len; i++)
		printf("%c", buffer->data[(buffer->ini + i) % BUF_CHAR_ALLOC]);
	printf("\n");
}

/**
 * @brief Libera da memória um buffer circular de caracteres.
 * @param buffer Buffer circular de caracteres a ser liberado da memória.
*/
void buf_char_circ_free(p_buf_char_circ buffer) {
	free(buffer);
}
