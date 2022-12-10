#define CITY_NAME_MAX_LEN 16

typedef struct map_node *p_map_node;

/**
 * @struct Nó de uma Árvore Binária de Busca que representa um mapa, organizada
 *         de acordo com os nomes das cidades.
 * @tparam city_name Nome da cidade.
 * @tparam visit_cnt Quantidade de visitas à cidade.
 * @tparam left Filho esquerdo.
 * @tparam right Filho direito.
*/
struct map_node {
	char city_name[CITY_NAME_MAX_LEN];
	int visit_cnt;
	p_map_node left;
	p_map_node right;
};

typedef struct visit_node *p_visit_node;

/**
 * @struct Nó de uma Árvore Binária de Busca que representa um histórico de
 *         visitas, organizada de acordo com as datas das visitas.
 * @tparam date Data da visita à cidade.
 * @tparam city_name Nome da cidade.
 * @tparam clue Presença de pista sobre o inimigo.
 * @tparam left Filho esquerdo.
 * @tparam right Filho direito.
*/
struct visit_node {
	int date;
	char city_name[CITY_NAME_MAX_LEN];
	int clue;
	p_visit_node left;
	p_visit_node right;
};

p_map_node map_node_insert(p_map_node root, char *city_name);

p_map_node map_node_search(p_map_node root, char *city_name);

p_map_node map_node_del(p_map_node root, char *city_name);

void map_tree_free(p_map_node root);

p_visit_node visit_node_insert(
	p_visit_node root,
	char *city_name,
	int date,
	int clue
);

p_visit_node visit_node_search(p_visit_node root, int date);

p_visit_node visit_node_del(p_visit_node root, int date);

void visit_node_print_dates(p_visit_node root, int date_ini, int date_end);

void visit_node_print_clues(p_visit_node root, int date_ini, int date_end);

void visit_tree_free(p_visit_node root);

void insere_visita(p_map_node *map_root, p_visit_node *visit_root);

void exclui_visita(p_map_node *map_root, p_visit_node *visit_root);

void relatorio_data(p_visit_node visit_root);

void relatorio_pista(p_visit_node visit_root);
