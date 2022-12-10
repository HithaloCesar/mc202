/**
 * @struct Processo criminal.
 * @tparam id Número identificador do processo.
 * @tparam name Nome do processo.
 * @tparam time Tempo de espera para o processo ser atendido, em dias.
 * @tparam deleted Estado de remoção do processo.
*/
typedef struct {
	int id;
	char name[32];
	int time;
	int deleted;
} lawsuit;

typedef lawsuit *p_lawsuit;

/**
 * @struct Tabela hash de processos.
 * @tparam data Vetor de processos, cujos índices são determinados por hash.
 * @tparam n Quantidade de processos na tabela hash.
 * @tparam m Tamanho da tabela hash.
*/
typedef struct {
	p_lawsuit *data;
	int n;
	int m;
} lawsuit_hashtable;

typedef lawsuit_hashtable *p_lawsuit_hashtable;

int prime_next(int n);

p_lawsuit_hashtable lawsuit_hahstable_resize(p_lawsuit_hashtable ht);

p_lawsuit_hashtable lawsuit_hashtable_create(int n);

int lawsuit_insert(p_lawsuit_hashtable h, int id, char *name, int time);

int lawsuit_search(p_lawsuit_hashtable h, int id);

int lawsuit_del(p_lawsuit_hashtable h, int id);

void lawsuit_hashtable_free(p_lawsuit_hashtable ht);
