#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "represa.h"

/** @brief Executa o programa principal, responsável por imprimir um relatório
 *         acerca dos níveis atuais de represas.
 *  @return Caso o programa seja executado com sucesso, retorna 0.
 */
int main(void) {
	int represas_cnt = 0;
	scanf("%d", &represas_cnt);
	char *name = malloc(101 * sizeof(char));
	int *lvls = malloc(1000 * sizeof(int));
	Represa *represas = malloc(represas_cnt * sizeof(Represa));
	for (int rep_idx = 0; rep_idx < represas_cnt; rep_idx++) {
		scanf("%s", name);
		float lvl_max;
		scanf("%f", &lvl_max);
		int lvl_cnt;
		scanf("%d", &lvl_cnt);
		for (int lvl_idx = 0; lvl_idx < lvl_cnt; lvl_idx++)
			scanf("%d", &lvls[lvl_idx]);
		represas[rep_idx] = represa_set(name, lvl_max, lvl_cnt, lvls);
	}
	free(name);
	free(lvls);
	for (int rep_idx = 0; rep_idx < represas_cnt; rep_idx++) {
		represas_name_fix(represas, represas_cnt);
		represa_print(represas[rep_idx]);
	}
	for (int rep_idx = 0; rep_idx < represas_cnt; rep_idx++) {
		free(represas[rep_idx].name);
		free(represas[rep_idx].lvls);
	}
	free(represas);
	return 0;
}
