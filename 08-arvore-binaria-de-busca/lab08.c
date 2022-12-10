#include <stdio.h>
#include <string.h>
#include "mapa.h"

/**
 * @brief Executa o programa principal, responsável por realizar operações sob
 *        árvores binárias de busca que representam cidades ou visitas em
 *        cidades.
 * @return Caso o programa seja executado com sucesso, retorna 0.
*/
int main(void) {
	int operation_cnt;
	scanf("%d", &operation_cnt);
	char operation[16];
	p_map_node map_root = NULL;
	p_visit_node visit_root = NULL;
	for (int i = 0; i < operation_cnt; i++) {
		scanf("%s", operation);
		if (strcmp(operation, "insere_visita") == 0)
			insere_visita(&map_root, &visit_root);
		else if (strcmp(operation, "exclui_visita") == 0)
			exclui_visita(&map_root, &visit_root);
		else if (strcmp(operation, "relatorio_data") == 0)
			relatorio_data(visit_root);
		else if (strcmp(operation, "relatorio_pista") == 0)
			relatorio_pista(visit_root);
	}
	map_tree_free(map_root);
	visit_tree_free(visit_root);
	return 0;
}
