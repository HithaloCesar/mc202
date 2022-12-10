#include <stdio.h>
#include "grafo.h"

/**
 * @brief Calcula a distância entre um centro de produção e um ponto de
 *        distribuição e, caso necessário, constrói um novo centro de produção.
 * @param graph_amz Grafo da empresa AMZ.
 * @param c_index Identificador do centro de produção em questão.
 * @param p_index Identificador do ponto de distribuição em questão.
 * @param distance_limit Distância que determinará a necessidade de construir
 *                       um novo centro de produção.
*/
void operation_distance(
		p_graph_adjacency_list graph_amz,
		int c_index,
		int p_index,
		int distance_limit) {
	int distance;
	distance = graph_bfs(graph_amz, c_index, p_index);
	printf("DISTANCIA %d -> %d = %d\n", c_index, p_index, distance);
	if (distance > distance_limit) {
		graph_node_insert(graph_amz);
		printf("%d ADICIONADO E CONECTADO A ", graph_amz->node_count - 1);
		for (
				p_linked_list_int adj_node = graph_amz->adjacency_list[p_index];
				adj_node != NULL;
				adj_node = adj_node->next) {
			graph_edge_insert(graph_amz, graph_amz->node_count - 1, adj_node->value);
			graph_amz->adjacency_list[graph_amz->node_count - 1] = (
				adjacency_sorted_insertion(
					graph_amz->adjacency_list[graph_amz->node_count - 1]
				)
			);
		}
		graph_edge_insert(graph_amz, graph_amz->node_count - 1, p_index);
		graph_amz->adjacency_list[graph_amz->node_count - 1] = (
			adjacency_sorted_insertion(
				graph_amz->adjacency_list[graph_amz->node_count - 1]
			)
		);
		for (
				p_linked_list_int adj_node = (
					graph_amz->adjacency_list[graph_amz->node_count - 1]
				);
				adj_node != NULL;
				adj_node = adj_node->next) {
			printf("%d", adj_node->value);
			if (adj_node->next != NULL)
				printf(" ");
		}
		printf("\n");
	}
}

/**
 * @brief Executa o código principal, responsável por gerenciar um grafo que
 *        representa centros de produção e pontos de distribuição de uma
 *        empresa.
 * @return Caso o programa seja executado com sucesso, retorna 0.
*/
int main(void) {
	int c_count, p_count;
	scanf("%d %d", &c_count, &p_count);
	p_graph_adjacency_list graph_amz = graph_create(c_count + p_count);
	int vertices_count;
	scanf("%d", &vertices_count);
	for (int i = 0; i < vertices_count; i++) {
		int vertex_1, vertex_2;
		scanf("%d %d", &vertex_1, &vertex_2);
		graph_edge_insert(graph_amz, vertex_1, vertex_2);
	}
	printf("GRAFO AMZ CONSTRUIDO!\n");
	int operation_count;
	scanf("%d", &operation_count);
	for (int i = 0; i < operation_count; i++) {
		char operation;
		int c_index, p_index, distance_limit;
		scanf(" %c", &operation);
		scanf("%d", &c_index);
		scanf("%d", &p_index);
		switch (operation) {
			case 'D':
				scanf("%d", &distance_limit);
				operation_distance(graph_amz, c_index, p_index, distance_limit);
				break;
			case 'R':
				graph_edge_remove(graph_amz, c_index, p_index);
				printf("ARESTA %d -> %d REMOVIDO\n", c_index, p_index);
				break;
		}
	}
	graph_free(graph_amz);
	return 0;
}
