#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

/**
 * @brief Insere um novo nó (cidade) em uma Árvore Binária de Busca (mapa)
 *        organizada de acordo com os nomes das cidades.
 * @param root Raiz da ABB.
 * @param city_name Nome da cidade a ser inserida no mapa.
 * @return Raiz da ABB.
*/
p_map_node map_node_insert(p_map_node root, char *city_name) {
	if (root == NULL) {
		p_map_node new_root = malloc(sizeof(struct map_node));
		strcpy(new_root->city_name, city_name);
		new_root->visit_cnt = 1;
		new_root->left = NULL;
		new_root->right = NULL;
		return new_root;
	}
	if (strcmp(root->city_name, city_name) > 0)
		root->left = map_node_insert(root->left, city_name);
	else
		root->right = map_node_insert(root->right, city_name);
	return root;
}

/**
 * @brief Procura por um nó (cidade) em uma Árvore Binária de Busca (mapa)
 *        organizada de acordo com os nomes das cidades.
 * @param root Raiz da ABB.
 * @param city_name Nome da cidade a ser procurada no mapa.
 * @return Nó (cidade) encontrado ou NULL.
*/
p_map_node map_node_search(p_map_node root, char *city_name) {
	while (root != NULL && strcmp(root->city_name, city_name) != 0) {
		if (strcmp(root->city_name, city_name) > 0)
			root = root->left;
		else
			root = root->right;
	}
	return root;
}

/**
 * @brief Exclui o sucessor de um nó (cidade) em uma Árvore Binária de Busca
 *        (mapa) organizada de acordo com os nomes das cidades.
 * @param root Nó (cidade) cujo sucessor deve ser excluído.
*/
void map_node_del_successor(p_map_node root) {
	p_map_node right_subtree_min = root->right;
	p_map_node parent = root;
	while (right_subtree_min->left != NULL) {
		parent = right_subtree_min;
		right_subtree_min = right_subtree_min->left;
	}
	if (parent->left == right_subtree_min)
		parent->left = right_subtree_min->right;
	else
		parent->right = right_subtree_min->right;
	strcpy(root->city_name, right_subtree_min->city_name);
	root->visit_cnt = right_subtree_min->visit_cnt;
	free(right_subtree_min);
}

/**
 * @brief Exclui um nó (cidade) de uma Árvore Binária de Busca (mapa)
 *        organizada de acordo com os nomes das cidades.
 * @param root Raiz da ABB.
 * @param city_name Nome da cidade cujo nó deve ser excluído.
 * @return Raiz da ABB ou NULL.
*/
p_map_node map_node_del(p_map_node root, char *city_name) {
	if (root == NULL)
		return NULL;
	if (strcmp(root->city_name, city_name) > 0)
		root->left = map_node_del(root->left, city_name);
	else if (strcmp(root->city_name, city_name) < 0)
		root->right = map_node_del(root->right, city_name);
	else if (root->left == NULL) {
		p_map_node right_root = root->right;
		free(root);
		return right_root;
	} else if (root->right == NULL) {
		p_map_node left_root = root->left;
		free(root);
		return left_root;
	} else
		map_node_del_successor(root);
	return root;
}

/**
 * @brief Libera da memória uma Árvore Binária de Busca que representa um mapa.
 * @param root Raiz da ABB.
*/
void map_tree_free(p_map_node root) {
	if (root != NULL) {
		map_tree_free(root->left);
		map_tree_free(root->right);
		free(root);
	}
}

/**
 * @brief Insere um novo nó (visita) em uma Árvore Binária de Busca (histórico
 *        de visitas) organizada de acordo com as datas das visitas.
 * @param root Raiz da ABB.
 * @param city_name Nome da cidade a ser inserida no histórico de visitas.
 * @param date Data da visita.
 * @param clue Presença de pista sobre o inimigo.
 * @return Raiz da ABB.
*/
p_visit_node visit_node_insert(
		p_visit_node root,
		char *city_name,
		int date,
		int clue) {
	if (root == NULL) {
		p_visit_node new_root = malloc(sizeof(struct visit_node));
		strcpy(new_root->city_name, city_name);
		new_root->date = date;
		new_root->clue = clue;
		new_root->left = NULL;
		new_root->right = NULL;
		return new_root;
	}
	if (root->date > date)
		root->left = visit_node_insert(root->left, city_name, date, clue);
	else
		root->right = visit_node_insert(root->right, city_name, date, clue);
	return root;
}

/**
 * @brief Procura por um nó (visita) em uma Árvore Binária de Busca (histórico
 *        de visitas) organizada de acordo com as datas das visitas.
 * @param root Raiz da ABB.
 * @param city_name Data da visita a ser procurada no histórico de visitas.
 * @return Nó (visita) encontrado ou NULL.
*/
p_visit_node visit_node_search(p_visit_node root, int date) {
	while (root != NULL && root->date != date) {
		if (root->date > date)
			root = root->left;
		else
			root = root->right;
	}
	return root;
}

/**
 * @brief Exclui o sucessor de um nó (visita) em uma Árvore Binária de Busca
 *        (histórico de visitas) organizada de acordo com as datas das visitas.
 * @param root Nó (visita) cujo sucessor deve ser excluído.
*/
void visit_node_del_successor(p_visit_node root) {
	p_visit_node right_subtree_min = root->right;
	p_visit_node parent = root;
	while (right_subtree_min->left != NULL) {
		parent = right_subtree_min;
		right_subtree_min = right_subtree_min->left;
	}
	if (parent->left == right_subtree_min)
		parent->left = right_subtree_min->right;
	else
		parent->right = right_subtree_min->right;
	root->date = right_subtree_min->date;
	strcpy(root->city_name, right_subtree_min->city_name);
	root->clue = right_subtree_min->clue;
	free(right_subtree_min);
}

/**
 * @brief Exclui um nó (visita) de uma Árvore Binária de Busca (hisórico de
 *        visitas) organizada de acordo com as datas das visitas.
 * @param root Raiz da ABB.
 * @param date Data da visita cujo nó deve ser excluído.
 * @return Raiz da ABB ou NULL.
*/
p_visit_node visit_node_del(p_visit_node root, int date) {
	if (root == NULL)
		return NULL;
	if (root->date > date)
		root->left = visit_node_del(root->left, date);
	else if (root->date < date)
		root->right = visit_node_del(root->right, date);
	else if (root->left == NULL) {
		p_visit_node right_root = root->right;
		free(root);
		return right_root;
	} else if (root->right == NULL) {
		p_visit_node left_root = root->left;
		free(root);
		return left_root;
	} else
		visit_node_del_successor(root);
	return root;
}

/**
 * @brief Imprime um relatório das visitas realizadas em determinado período,
 *        da mais antiga à mais recente.
 * @param root Raiz da Árvore Binária de Busca que representa um histórico de
 *             visitas, organizada a partir das datas das visitas.
 * @param date_ini Data inicial do período a ser considerada no relatório.
 * @param date_end Data final do período a ser considerado no relatório.
*/
void visit_node_print_dates(p_visit_node root, int date_ini, int date_end) {
	if (root == NULL)
		return;
	if (root->date > date_ini && root->left != NULL)
		visit_node_print_dates(root->left, date_ini, date_end);
	else if (root->date < date_ini && root->right != NULL)
		visit_node_print_dates(root->right, date_ini, date_end);
	if (root->date <= date_end && root->date >= date_ini) {
		printf("DATA: %d\n", root->date);
		printf("CIDADE: %s\n", root->city_name);
		printf("####\n");
		visit_node_print_dates(root->right, date_ini, date_end);
	}
}

/**
 * @brief Imprime um relatório das pistas encontradas em determinado período,
 *        da mais recente à mais antiga.
 * @param root Raiz da Árvore Binária de Busca que representa um histórico de
 *             visitas, organizada a partir das datas das visitas.
 * @param date_ini Data inicial do período a ser considerada no relatório.
 * @param date_end Data final do período a ser considerado no relatório.
*/
void visit_node_print_clues(p_visit_node root, int date_ini, int date_end) {
	if (root == NULL)
		return;
	if (root->date < date_end && root->right != NULL)
		visit_node_print_clues(root->right, date_ini, date_end);
	else if (root->date > date_end && root->left != NULL)
		visit_node_print_clues(root->left, date_ini, date_end);
	if (root->date >= date_ini && root->date <= date_end) {
		if (root->clue != 0) {
			printf("DATA: %d\n", root->date);
			printf("CIDADE: %s\n", root->city_name);
			printf("####\n");
		}
		visit_node_print_clues(root->left, date_ini, date_end);
	}
}

/**
 * @brief Libera da memória uma Árvore Binária de Busca que representa um
 *        histórico de visitas.
 * @param root Raiz da ABB.
*/
void visit_tree_free(p_visit_node root) {
	if (root != NULL) {
		visit_tree_free(root->left);
		visit_tree_free(root->right);
		free(root);
	}
}

/**
 * @brief Operação responsável pela inserção de visitas nas ABB que representam
 *        o mapa e o histórico de visitas.
 * @param map_root Endereço da raiz da ABB que representa o mapa.
 * @param visit_root Endereço da raiz da ABB que representa o histórico de
 *                   visitas.
*/
void insere_visita(p_map_node *map_root, p_visit_node *visit_root) {
	char city_name[CITY_NAME_MAX_LEN];
	int date, clue;
	scanf("%s", city_name);
	scanf("%d", &date);
	scanf("%d", &clue);
	p_map_node map_node_found = map_node_search(*map_root, city_name);
	if (map_node_found == NULL)
		*map_root = map_node_insert(*map_root, city_name);
	else
		map_node_found->visit_cnt++;
	*visit_root = visit_node_insert(*visit_root, city_name, date, clue);
	if (map_node_found == NULL) {
		printf("ARVORE: MAPA\n");
		printf("CIDADE: %s\n", city_name);
		printf("INSERIDO COM SUCESSO!\n");
		printf("####\n");
	}
	printf("ARVORE: VISITA\n");
	printf("DATA: %d\n", date);
	printf("CIDADE: %s\n", city_name);
	printf("INSERIDO COM SUCESSO!\n");
	printf("####\n");
}

/**
 * @brief Operação responsável pela exclusão de visitas nas ABB que representam
 *        o mapa e o histórico de visitas.
 * @param map_root Endereço da raiz da ABB que representa o mapa.
 * @param visit_root Endereço da raiz da ABB que representa o histórico de
 *                   visitas.
*/
void exclui_visita(p_map_node *map_root, p_visit_node *visit_root) {
	int date;
	scanf("%d", &date);
	p_visit_node visit_node_found = visit_node_search(*visit_root, date);
	p_map_node map_node_found = map_node_search(
		*map_root, visit_node_found->city_name
	);
	map_node_found->visit_cnt--;
	printf("CIDADE: %s\n", map_node_found->city_name);
	printf("QUANTIDADE DE VISITAS RESTANTES: %d\n", map_node_found->visit_cnt);
	printf("####\n");
	*visit_root = visit_node_del(*visit_root, date);
	if (map_node_found->visit_cnt == 0)
		*map_root = map_node_del(*map_root, map_node_found->city_name);
}

/**
 * @brief Operação responsável pela impressão do relatório das visitas
 *        realizadas em determinado período, da mais antiga à mais recente.
 * @param visit_root Raiz da ABB que representa o histórico de visitas.
*/
void relatorio_data(p_visit_node visit_root) {
	int date_ini, date_end;
	scanf("%d", &date_ini);
	scanf("%d", &date_end);
	printf("--VISITAS--\n");
	visit_node_print_dates(visit_root, date_ini, date_end);
}

/**
 * @brief Operação responsável pela impressão do relatório das pistas
 *        encontradas em determinado período, da mais recente à mais antiga.
 * @param visit_root Raiz da ABB que representa o histórico de visitas.
*/
void relatorio_pista(p_visit_node visit_root) {
	int date_ini, date_end;
	scanf("%d", &date_ini);
	scanf("%d", &date_end);
	printf("--PISTAS--\n");
	visit_node_print_clues(visit_root, date_ini, date_end);
}
