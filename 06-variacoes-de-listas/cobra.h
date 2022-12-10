typedef struct coords_2d *p_coords_2d;

/** @struct Coordenadas inteiras para um ponto em um espaço 2D.
 *  @tparam row Linha do ponto.
 *  @tparam col Coluna do ponto.
 */
struct coords_2d {
	int row;
	int col;
};

typedef struct dll_coords_2d_node *p_dll_coords_2d_node;

/** @struct Nó de uma lista duplamente ligada, com coordenadas inteiras para um
 *          ponto em um espaço 2D.
 *  @tparam prev Ponteiro para o nó anterior.
 *  @tparam next Ponteiro para o nó sucessor.
 *  @tparam coords Coordenadas inteiras para um ponto em um espaço 2D.
 */
struct dll_coords_2d_node {
	p_dll_coords_2d_node prev;
	p_dll_coords_2d_node next;
	p_coords_2d coords;
};

typedef struct dll_coords_2d *p_dll_coords_2d;

/** @struct Lista duplamente ligada, cujos nós armazenam coordenadas inteiras
 *          para um ponto em um espaço 2D.
 *  @tparam first Ponteiro para o primeiro nó da lista.
 *  @tparam last Ponteiro para o último nó da lista.
 *  @tparam len Quantidade de nós na lista.
 */
struct dll_coords_2d {
	p_dll_coords_2d_node first;
	p_dll_coords_2d_node last;
	int len;
};

typedef struct matrix_char *p_matrix_char;

/** @struct Matriz de caracteres.
 *  @tparam data Conteúdo da matriz.
 *  @tparam row_cnt Quantidade de linhas ocupadas na matriz.
 *  @tparam rows_alloc Quantidade de linhas alocadas para a matriz.
 *  @tparam col_cnt Quantidade de colunas ocupadas na matriz.
 *  @tparam cols_alloc Quantidade de colunas alocadas para a matriz.
 */
struct matrix_char {
	char **data;
	int row_cnt;
	int rows_alloc;
	int col_cnt;
	int cols_alloc;
};

/** @brief Cria uma nova matriz de caracteres, ou seja, aloca-a na memória e
 *         define a contagem de linhas e colunas para zero.
 *  @param rows_alloc Quantidade de linhas a serem alocadas na matriz.
 *  @param cols_alloc Quantidade de colunas a serem alocadas na matriz.
 *  @return A matriz de caracteres criada.
 */
p_matrix_char matrix_char_create(int rows_alloc, int cols_alloc);

/** @brief Preenche completamente uma matriz de caracteres com um caractere e
 *         altera as dimensões para compreender todo o espaço alocado.
 *  @param matrix Matriz a ser preenchida.
 *  @param c Caractere a ser inserido em todas as entradas da matriz.
 */
void matrix_char_fill(p_matrix_char matrix, char c);

/** @brief Permite a inserção de uma fruta no mapa do jogo snake.
 *  @param command String que deve receber "FRUTA" para o sucesso da função.
 *  @param fruit Coordenadas da fruta no mapa.
 *  @param map Mapa do jogo snake.
 */
void fruit_insert(char *command, p_coords_2d fruit, p_matrix_char map);

/** @brief Permite a inserção da cobra no mapa do jogo snake.
 *  @param command String que deve receber "COBRA" para o sucesso da função.
 *  @param map Matriz de caracteres que representa o mapa do jogo snake.
 *  @return Lista duplamente ligada que representa a cobra.
 */
p_dll_coords_2d snake_insert(char *command, p_matrix_char map);

/** @brief Cria uma lista duplamente ligada com coordenadas 2D.
 *  @param row Linha do ponto do primeiro nó.
 *  @param col Coluna do ponto do primeiro nó.
 *  @return Lista duplamente ligada criada.
 */
p_dll_coords_2d dll_coords_2d_create(int row, int col);

/** @brief Imprime uma matriz de caracteres.
 *  @param matrix Matriz a ser impressa.
 */
void matrix_char_print(p_matrix_char matrix);

/** @brief Lê um caractere que referencia a direção da movimentação e define as
 *         coordenadas do destino da cabeça da cobra.
 *  @param dest Coordenadas 2D do destino da cabeça da cobra.
 *  @param snake Cobra, representada por uma lista duplamente ligada com
 *               coordenadas 2D.
 *  @param map Matriz de caracteres que representa o mapa do jogo snake.
 */
void dest_coords_set(
	p_coords_2d dest,
	p_dll_coords_2d snake,
	p_matrix_char map
);

/** @brief Executa o movimento da cobra no jogo snake.
 *  @param snake Cobra, representada por uma lista duplamente ligada com
 *               coordenadas 2D.
 *  @param dest Coordenadas 2D do destino da cabeça da cobra.
 *  @param map Matriz de caracteres que representa o mapa do jogo snake.
 */
void snake_move(p_dll_coords_2d snake, p_coords_2d dest, p_matrix_char map);

/** @brief Aumenta o tamanho da cobra no jogo snake.
 *  @param snake Cobra, representada por uma lista duplamente ligada com
 *               coordenadas 2D.
 *  @param dest Coordenadas 2D do destino da cabeça da cobra.
 *  @param map Matriz de caracteres que representa o mapa do jogo snake.
 */
void snake_eat(p_dll_coords_2d snake, p_coords_2d dest, p_matrix_char map);

/** @brief Libera da memória uma matriz de caracteres.
 *  @param matrix Matriz de caracteres a ser liberada.
 */
void matrix_char_free(p_matrix_char matrix);

/** @brief Libera da memória os nós de uma lista duplamente ligada com
 *         coordenadas 2D e a lista em si.
 *  @param list Lista duplamente ligada.
 */
void dll_coords_2d_free(p_dll_coords_2d list);
