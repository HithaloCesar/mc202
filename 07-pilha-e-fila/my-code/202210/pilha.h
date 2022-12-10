#define LL_STRING_ALLOC 50

typedef struct ll_string_node *p_ll_string_node;

/**
 * @brief Nó de uma lista ligada de strings.
 * @tparam data String do nó.
 * @tparam len Tamanho da string do nó.
*/
struct ll_string_node {
	char data[LL_STRING_ALLOC];
	int len;
	p_ll_string_node next;
};

typedef struct stack_string *p_stack_string;

/**
 * @brief Pilha de strings.
 * @tparam top Último nó adicionado.
 * @tparam len Tamanho da pilha.
*/
struct stack_string {
	p_ll_string_node top;
	int len;
};

/**
 * @brief Gera uma pilha de strings.
 * @return Pilha de strings gerada.
*/
p_stack_string stack_string_create(void);

/**
 * @brief Insere um caractere em uma pilha de strings.
 * @param stack Pilha de strings na qual o caractere deve ser inserido.
 * @param c Caractere a ser inserido na pilha de strings.
*/
void stack_string_char_insert(p_stack_string stack, char c);

/**
 * @brief Deleta certa quantidade de caracteres de uma pilha de strings.
 * @param stack Pilha de strings em que ocorrerá a remoção de caracteres.
 * @param cnt Quantidade de caracteres a serem removidos da pilha de strings.
*/
void stack_string_char_del_cnt(p_stack_string stack, int cnt);

/**
 * @brief Imprime na tela o conteúdo de uma pilha de strings.
 * @param stack Pilha de strings a ser impressa na tela.
*/
void stack_string_print(p_stack_string stack);

/**
 * @brief Libera da memória uma pilha de strings.
 * @param stack Pilha de strings a ser liberada da memória.
*/
void stack_string_free(p_stack_string stack);
