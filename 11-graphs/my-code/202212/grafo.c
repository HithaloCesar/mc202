#include <stdlib.h>
#include "grafo.h"

/**
 * @brief Cria um grafo cujos representado por uma lista de adjacências.
 * @param node_count Quantidade de nós a serem criados no grafo.
 * @return Grafo criado.
*/
p_graph_adjacency_list graph_create(int node_count) {
	p_graph_adjacency_list new_graph = malloc(
		sizeof(struct graph_adjacency_list)
	);
	new_graph->alloc_count = node_count;
	new_graph->node_count = node_count;
	new_graph->adjacency_list = malloc(
		new_graph->alloc_count * sizeof(p_linked_list_int)
	);
	for (int i = 0; i < node_count; i++)
		new_graph->adjacency_list[i] = NULL;
	return new_graph;
}

/**
 * @brief Insere um nó numa lista de adjacência.
 * @param head Primeiro nó da lista de adjacência.
 * @param node_index Índice do nó a ser inserido na lista de adjacência.
 * @return Novo primeiro nó da lista de adjacência.
*/
p_linked_list_int graph_adjacency_insert(
		p_linked_list_int head,
		int node_index) {
	p_linked_list_int new_head = malloc(sizeof(struct linked_list_int));
	new_head->value = node_index;
	new_head->next = head;
	return new_head;
}

/**
 * @brief Insere uma aresta em um grafo representado por uma lista de
 *        adjacências.
 * @param graph Grafo representado por uma lista de adjacências.
 * @param node_1_index Índice do primeiro nó.
 * @param node_2_index Índice do segundo nó.
*/
void graph_edge_insert(
		p_graph_adjacency_list graph,
		int node_1_index,
		int node_2_index) {
	graph->adjacency_list[node_1_index] = graph_adjacency_insert(
		graph->adjacency_list[node_1_index], node_2_index
	);
	graph->adjacency_list[node_2_index] = graph_adjacency_insert(
		graph->adjacency_list[node_2_index], node_1_index
	);
}

/**
 * @brief Gera um buffer circular de inteiros.
 * @param alloc_count Espaços para inteiro a serem alocados no buffer.
 * @return Buffer circular de inteiros gerado.
*/
p_buffer_int buffer_int_create(int alloc_count) {
	p_buffer_int buffer = malloc(sizeof(struct buffer_int));
	buffer->data = malloc(alloc_count * sizeof(int));
	buffer->alloc_count = alloc_count;
	buffer->lenght = 0;
	buffer->ini = 0;
	buffer->end = 0;
	return buffer;
}

/**
 * @brief Insere um número inteiro num buffer de inteiros.
 * @param buffer Buffer circular no qual o inteiro deve ser inserido.
 * @param insert_value Inteiro a ser inserido no buffer circular de inteiros.
*/
void buffer_insert(p_buffer_int buffer, int insert_value) {
	buffer->data[buffer->end] = insert_value;
	buffer->end = (buffer->end + 1) % buffer->alloc_count;
	buffer->lenght++;
}

/**
 * @brief Remove um inteiro de um buffer de inteiros.
 * @param buffer Buffer circular de onde o inteiro será resolvido.
 * @result Inteiro removido do buffer.
*/
int buffer_pop(p_buffer_int buffer) {
	int pop_value = buffer->data[buffer->ini];
	buffer->ini = (buffer->ini + 1) % buffer->alloc_count;
	buffer->lenght--;
	return pop_value;
}

/**
 * @brief Procura pela menor distância entre dois nós de um grafo representado
 *        por uma lista de adjacências.
 * @param graph Grafo representado por uma lista de adjacências.
 * @param origin_node_index Índice do nó origem.
 * @param destiny_node_index Índice do nó destino.
 * @return Menor distância encontrada entre o dois nós.
*/
int graph_bfs(
		p_graph_adjacency_list graph,
		int origin_node_index,
		int destiny_node_index) {
	int *visited = malloc(graph->node_count * sizeof(int));
	int *distance = malloc(graph->node_count * sizeof(int));
	int *parent = malloc(graph->node_count * sizeof(int));
	for (int i = 0; i < graph->node_count; i++) {
		visited[i] = 0;
		parent[i] = -1;
		distance[i] = __INT_MAX__;
	}
	p_buffer_int queue = buffer_int_create(graph->node_count);
	buffer_insert(queue, origin_node_index);
	visited[origin_node_index] = 1;
	parent[origin_node_index] = origin_node_index;
	distance[origin_node_index] = 0;
	p_linked_list_int adj_node;
	int node_found = 0;
	int min_distance = __INT_MAX__;
	while (queue->lenght != 0 && !node_found) {
		int node_value = buffer_pop(queue);
		for (
				adj_node = graph->adjacency_list[node_value];
				adj_node != NULL;
				adj_node = adj_node->next)
			if (!visited[adj_node->value]) {
				visited[adj_node->value] = 1;
				parent[adj_node->value] = node_value;
				distance[adj_node->value] = distance[parent[adj_node->value]] + 1;
				buffer_insert(queue, adj_node->value);
				if (adj_node->value == destiny_node_index) {
					min_distance = distance[adj_node->value];
					node_found = 1;
					break;
				}
			}
	}
	free(visited);
	free(distance);
	free(parent);
	free(queue->data);
	free(queue);
	return min_distance;
}

/**
 * @brief Insere um nó num grafo representado por uma lista de adjacências.
 * @param graph Grafo representado por uma lista de adjacências.
*/
void graph_node_insert(p_graph_adjacency_list graph) {
	if (graph->node_count == graph->alloc_count) {
		graph->alloc_count *= 2;
		graph->adjacency_list = realloc(
			graph->adjacency_list, graph->alloc_count * sizeof(p_linked_list_int)
		);
		for (
				int node_index = graph->node_count;
				node_index < graph->alloc_count;
				node_index++)
			graph->adjacency_list[node_index] = NULL;
	}
	graph->node_count++;
}

/**
 * @brief Organiza o primeiro nó de uma lista de adjacência.
 * @param head Primeiro nó da lista de adjacência.
 * @return Novo primeiro nó da lista de adjacência.
*/
p_linked_list_int adjacency_sorted_insertion(p_linked_list_int head) {
	if (head == NULL || head->next == NULL || head->value <= head->next->value)
		return head;
	p_linked_list_int new_node = head;
	head = head->next;
	p_linked_list_int current_node;
	for (current_node = head;
			current_node->next != NULL
			&& current_node->next->value < new_node->value;
			current_node = current_node->next) {}
	new_node->next = current_node->next;
	current_node->next = new_node;
	return head;
}

/**
 * @brief Remove um nó de uma lista de adjacência.
 * @param head Primeiro nó da lista de adjacência.
 * @param node_index Índice do nó a ser removido da lista de adjacência.
 * @return Novo primeiro nó da lista de adjacência.
*/
p_linked_list_int graph_adjacency_remove(
		p_linked_list_int head,
		int node_index) {
	if (head == NULL)
		return NULL;
	p_linked_list_int new_head;
	if (head->value == node_index) {
		new_head = head->next;
		free(head);
		return new_head;
	}
	head->next = graph_adjacency_remove(head->next, node_index);
	return head;
}

/**
 * @brief Remove uma aresta em um grafo representado por uma lista de
 *        adjacências.
 * @param graph Grafo representado por uma lista de adjacências.
 * @param node_1_index Índice do primeiro nó.
 * @param node_2_index Índice do segundo nó.
*/
void graph_edge_remove(
		p_graph_adjacency_list graph,
		int node_1_index,
		int node_2_index) {
	graph->adjacency_list[node_1_index] = graph_adjacency_remove(
			graph->adjacency_list[node_1_index], node_2_index
	);
	graph->adjacency_list[node_2_index] = graph_adjacency_remove(
		graph->adjacency_list[node_2_index], node_1_index
	);
}

/**
 * @brief Libera da memória uma lista ligada de inteiros.
 * @param head Primeiro nó da lista ligada de inteiros.
*/
void linked_list_int_free(p_linked_list_int head) {
	if (head != NULL) {
		linked_list_int_free(head->next);
		free(head);
	}
}

/**
 * @brief Libera da memória um grafo representado por uma lista de adjacência.
 * @param graph Grafo a ser destruído.
*/
void graph_free(p_graph_adjacency_list graph) {
	for (
			int adjacency_index = 0;
			adjacency_index < graph->alloc_count;
			adjacency_index++)
		linked_list_int_free(graph->adjacency_list[adjacency_index]);
	free(graph->adjacency_list);
	free(graph);
}
