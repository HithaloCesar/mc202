#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/**
 * @brief Gera uma pilha de strings.
 * @return Pilha de strings gerada.
*/
p_stack_string stack_string_create(void) {
	p_ll_string_node node = malloc(sizeof(struct ll_string_node));
	node->len = 0;
	node->next = NULL;
	p_stack_string stack = malloc(sizeof(struct stack_string));
	stack->top = node;
	return stack;
}

/**
 * @brief Insere um nó em uma pilha de strings.
 * @param stack Pilha de strings na qual um novo nó deve ser inserido.
*/
void stack_string_node_insert(p_stack_string stack) {
	p_ll_string_node new_node = malloc(sizeof(struct ll_string_node));
	new_node->len = 0;
	new_node->next = stack->top;
	stack->top = new_node;
	stack->len++;
}

/**
 * @brief Insere um caractere em uma pilha de strings.
 * @param stack Pilha de strings na qual o caractere deve ser inserido.
 * @param c Caractere a ser inserido na pilha de strings.
*/
void stack_string_char_insert(p_stack_string stack, char c) {
	if (stack->top->len == LL_STRING_ALLOC)
		stack_string_node_insert(stack);
	stack->top->data[stack->top->len] = c;
	if (c != '\0')
		stack->top->len++;
}

/**
 * @brief Deleta um nó de uma pilha de strings.
 * @param stack Pilha de strings em que um nó deve ser removido.
*/
void stack_string_node_del(p_stack_string stack) {
	if (stack->top == NULL)
		return;
	p_ll_string_node top = stack->top;
	stack->top = stack->top->next;
	free(top);
	stack->len--;
}

/**
 * @brief Deleta certa quantidade de caracteres de uma pilha de strings.
 * @param stack Pilha de strings em que ocorrerá a remoção de caracteres.
 * @param cnt Quantidade de caracteres a serem removidos da pilha de strings.
*/
void stack_string_char_del_cnt(p_stack_string stack, int cnt) {
	if (stack->top == NULL)
		return;
	while (cnt >= stack->top->len) {
		cnt -= stack->top->len;
		stack_string_node_del(stack);
		if (stack->top == NULL)
			return;
	}
	stack->top->len -= cnt;
	stack_string_char_insert(stack, '\0');
}

/**
 * @brief Imprime na tela o conteúdo de uma lista ligada de strings.
 * @param node Primeiro nó da lista ligada de strings.
*/
void ll_string_print(p_ll_string_node node) {
	if (node->next != NULL)
		ll_string_print(node->next);
	for (int char_idx = 0; char_idx < node->len; char_idx++)
		printf("%c", node->data[char_idx]);
}

/**
 * @brief Imprime na tela o conteúdo de uma pilha de strings.
 * @param stack Pilha de strings a ser impressa na tela.
*/
void stack_string_print(p_stack_string stack) {
	ll_string_print(stack->top);
	printf("\n");
}

/**
 * @brief Libera da memória os nós de uma lista ligada de strings.
 * @param node Primeiro nó da lista ligada de strings.
*/
void ll_string_free(p_ll_string_node node) {
	if (node == NULL)
		return;
	p_ll_string_node next = node->next;
	free(node);
	ll_string_free(next);
}

/**
 * @brief Libera da memória uma pilha de strings.
 * @param stack Pilha de strings a ser liberada da memória.
*/
void stack_string_free(p_stack_string stack) {
	ll_string_free(stack->top);
	free(stack);
}
