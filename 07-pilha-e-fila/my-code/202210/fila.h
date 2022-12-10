#define BUF_CHAR_ALLOC 500

typedef struct buf_char_circ *p_buf_char_circ;

/**
 * @brief Buffer circular de caracteres.
 * @tparam data Caracteres presentes no buffer.
 * @tparam ini Índice do caractere a ser processado.
 * @tparam end Índice do caractere a ser inserido.
 * @tparam len Quantidade de caracteres no buffer.
*/
struct buf_char_circ {
	char data[BUF_CHAR_ALLOC];
	int ini;
	int end;
	int len;
};

/**
 * @brief Gera um buffer circular de caracteres.
 * @return Buffer circular de caracteres gerado.
*/
p_buf_char_circ buf_char_circ_create(void);

/**
 * @brief Insere uma string no buffer.
 * @param buffer Buffer circular de caracteres que receberá a string.
 * @param string String a ser copiada para o buffer.
*/
void buffer_circ_str_insert(p_buf_char_circ buffer, char* string);

/**
 * @brief Ejeta um caractere de um buffer circular de caracteres.
 * @param buffer Buffer circular de caracteres em que haverá a expulsão de um
 *               caractere.
 * @return Caractere removido do buffer circular de caracteres.
*/
char buf_char_circ_pop(p_buf_char_circ buffer);

/**
 * @brief Imprime na tela o conteúdo de um buffer circular de caracteres.
 * @param buffer Buffer circular de caracteres a ser impresso na tela.
*/
void buf_char_circ_print(p_buf_char_circ buffer);

/**
 * @brief Libera da memória um buffer circular de caracteres.
 * @param buffer Buffer circular de caracteres a ser liberado da memória.
*/
void buf_char_circ_free(p_buf_char_circ buffer);
