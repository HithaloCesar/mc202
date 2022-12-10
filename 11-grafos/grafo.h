typedef struct linked_list_int *p_linked_list_int;

/**
 * @struct Lista ligada de inteiros.
 * @tparam value Valor atribuído ao nó.
 * @tparam next Ponteiro para o próximo nó.
*/
struct linked_list_int {
	int value;
	p_linked_list_int next;
};

typedef struct graph_adjacency_list *p_graph_adjacency_list;

/**
 * @struct Grafo representado por uma lista de adjacências.
 * @tparam adjacency_list Vetor de listas ligadas que representam as
 *         adjacências de cada nó.
 * @tparam node_count Quantidade de nós no grafo.
 * @tparam allocs_count Quantidade de nós alocados para o grafo.
*/
struct graph_adjacency_list {
	p_linked_list_int *adjacency_list;
	int node_count;
	int alloc_count;
};

typedef struct buffer_int *p_buffer_int;

/**
 * @struct Buffer de inteiros.
 * @tparam data Vetor do buffer.
 * @tparam ini Índice inicial do buffer.
 * @tparam end Índice no qual deve ser inserido um novo inteiro, se necessário.
 * @tparam lenght Espaços ocupados no buffer.
 * @tparam alloc_count Espaços disponíveis (alocados) no buffer.
*/
struct buffer_int {
	int *data;
	int ini;
	int end;
	int lenght;
	int alloc_count;
};

p_graph_adjacency_list graph_create(int node_count);

void graph_edge_insert(
	p_graph_adjacency_list graph,
	int node_1_index,
	int node_2_index
);

int graph_bfs(
	p_graph_adjacency_list graph,
	int origin_node_index,
	int destiny_node_index
);

void graph_node_insert(p_graph_adjacency_list graph);

p_linked_list_int adjacency_sorted_insertion(p_linked_list_int head);

void graph_edge_remove(
	p_graph_adjacency_list graph,
	int node_1_index,
	int node_2_index
);

void graph_free(p_graph_adjacency_list graph);
