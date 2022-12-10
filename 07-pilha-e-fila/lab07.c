#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pilha.h"
#include "fila.h"
#define BUF_LEN 500

/**
 * @brief Executa o programa principal, que simula um simples editor de texto.
 * @return Caso o programa seja executado com sucesso, retorna 0.
*/
int main(void) {
	char buffer[500];
	p_buf_char_circ queue = buf_char_circ_create();
	p_stack_string stack = stack_string_create();
	bool resume = true;
	while (resume) {
		fgets(buffer, 500, stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		if (strncmp(buffer, "EXEC ", 5) == 0) {
			int cnt;
			sscanf(buffer + 5, "%d", &cnt);
			for (int i = 0; i < cnt; i++)
				stack_string_char_insert(stack, buf_char_circ_pop(queue));
			stack_string_char_insert(stack, '\0');
		} else if (strncmp(buffer, "DEL ", 4) == 0) {
			int cnt;
			sscanf(buffer + 4, "%d", &cnt);
			stack_string_char_del_cnt(stack, cnt);
		} else if (strcmp(buffer, "EXIT") == 0)
			resume = false;
		else
			buffer_circ_str_insert(queue, buffer);
		if (resume) {
			printf("FILA ATUAL: ");
			buf_char_circ_print(queue);
			printf("PILHA ATUAL: ");
			stack_string_print(stack);
			printf("####\n");
		}
	}
	stack_string_free(stack);
	buf_char_circ_free(queue);
	return 0;
}
