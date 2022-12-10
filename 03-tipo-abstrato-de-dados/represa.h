/** @struct Represa represa.h represa.h
 *  @brief Representa uma represa, com nome e dados sobre seus níveis medidos
 *         em determinado dia.
 *  @tparam name Nome da represa.
 *  @tparam lvl_max Capacidade máxima da represa.
 *  @tparam lvl_cnt Quantidade de medidas de níveis no dia.
 *  @tparam lvls Níveis medidos no dia.
 *  @tparam lvl_avg Média dos níveis medidos no dia.
 */
typedef struct {
  char *name;
  float lvl_max;
  int lvl_cnt;
  int *lvls;
  int lvl_avg;
} Represa;

/** @brief Gera uma represa com nome e dados sobre seus níveis medidos em
 *         determinado dia.
 *  @param name Nome da represa.
 *  @param lvl_max Capacidade máxima da represa.
 *  @param lvl_cnt Quantidade de medidas de níveis no dia.
 *  @param lvls Níveis medidos no dia.
 *  @return A represa gerada, com o nome, os dados e a média dos níveis.
 */
Represa represa_set(char *name, float lvl_max, int lvl_cnt, int *lvls);

/** @brief Informa se o alerta de nível da represa deve ser acionado, ou seja,
 *         se algum nível medido no dia é maior que 90% do nível máximo da
 *         represa.
 *  @param represa A represa cujos níveis devem ser analisados.
 *  @return Se o alerta for acionado, retorna 1. Caso contrário, retorna 0.
 */
int represa_alert(Represa represa);

/** @brief Imprime as informações de uma represa.
 *  @param represa A represa cujos dados devem ser impressos.
 */
void represa_print(Represa represa);

/** @brief Corrige nomes de represas, ou seja, remove o prefixo "represa_de_",
 *         troca underscores por espaços, transforma em lowercase e remove
 *         números à direita.
 *  @param represas Represas cujos nomes devem ser corrigidos.
 *  @param represas_cnt Quantidade de represas no vetor de represa.
 */
void represas_name_fix(Represa *represas, int represas_cnt);
