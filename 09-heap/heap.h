/**
 * @struct Processo criminal.
 * @tparam C Código de prioridade do processo.
 * @tparam P Número identificador do processo.
*/
typedef struct {
	int C;
	int P;
} lawsuit;

/**
 * @struct Fila de prioridade de processos.
 * @tparam data Vetor de processos.
 * @tparam cnt Quantidade de processos no vetor.
 * @tparam alloc Quantidade de processos alocados no vetor.
*/
typedef struct {
	lawsuit *data;
	int cnt;
	int alloc;
} lawsuit_heap;

typedef lawsuit_heap *p_lawsuit_heap;

p_lawsuit_heap lawsuit_heap_create(int alloc);

void lawsuit_heap_insert(p_lawsuit_heap heap, int P, int C);

lawsuit lawsuit_heap_extract(p_lawsuit_heap heap);

void lawsuit_heap_priority_change(p_lawsuit_heap heap, int P, int C);
