#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "represa.h"

/** @brief Informa o comprimento de uma string.
 *  @param string A string cujo comprimento deve ser informado.
 *  @return O comprimento da string.
 */
int string_length(char *string) {
	int cnt = 0;
	while (string[cnt] != '\0' && string[cnt] != '\n')
		cnt++;
	return cnt;
}

/** @brief Copia uma string.
 *  @param string A string a ser copiada.
 *  @return Um ponteiro para a cópia da string.
 */
char *string_copy(char *string) {
	int string_len = string_length(string);
	char *copy = malloc((string_len + 1) * sizeof(char));
	for (int i = 0; i < string_len + 1; i++)
		copy[i] = string[i];
	return copy;
}

/** @brief Calcula a média de inteiros.
 *  @param v Inteiros cuja média deve ser calculada.
 *  @param v_cnt Quantidade de inteiros.
 *  @return A média truncada.
 */
int int_avg_truncated(
		int *v,
		int v_cnt) {
	int sum = 0;
	for (int i = 0; i < v_cnt; i++)
		sum += v[i];
	int average = sum / v_cnt;
	return average;
}

/** @brief Copia um vetor de inteiros.
 *  @param v Inteiros a serem copiados.
 *  @param v_cnt Quantidade de inteiros.
 *  @return Um ponteiro para a cópia do vetor de inteiros.
 */
int *int_copy(
		int *v,
		int v_cnt) {
	int *copy = malloc(v_cnt * sizeof(int));
	for (int i = 0; i < v_cnt; i++)
		copy[i] = v[i];
	return copy;
}

/** @brief Informa se um caractere é uma letra do alfabeto.
 *  @param c O caractere a ser analisado.
 *  @return Se o caractere for uma letra do alfabeto, retorna true. Caso
 *          contrário, retorna false.
 */
bool char_is_alphabet(char c) {
	if (c >= 65 && c <= 122)
		return true;
	return false;
}

/** @brief Informa se um caractere é uppercase.
 *  @param c O caractere a ser analisado.
 *  @return Se o caractere for uppercase, retorna true. Caso contrário, retorna
 *          false.
 */
bool char_is_upper(char c) {
	if (c >= 65 && c <= 90)
		return true;
	return false;
}

/** @brief Informa se um caractere é lowercase.
 *  @param c O caractere a ser analisado.
 *  @return Se o caractere for lowercase, retorna true. Caso contrário, retorna
 *          false.
 */
bool char_is_lower(char c) {
	if (c >= 97 && c <= 122)
		return true;
	return false;
}

/** @brief Devolve uma letra do alfabeto com a capitalização trocada.
 *  @param c O caractere cuja capitalização deve ser trocada.
 *  @return Se o caractere for uppercase, retorna sua versão lowercase. Se o
 *          caractere for lowercase, retorna sua versão uppercase.
 */
char char_case_switch(char c) {
	if (char_is_upper(c))
		return c + 32;
	return c - 32;
}

/** @brief Informa se dois caracteres são iguais, considerando a capitalização
 *         ou não.
 *  @param a Um dos caracteres a ser comparado.
 *  @param b O outro caractere a ser comparado.
 *  @param case_sen Sensibilidade à capitalização.
 *  @return Se os dois caracteres forem iguais, considerando a capitalização ou
 *          não, retorna true. Caso contrário, retorna false.
 */
bool char_compare(
		char a,
		char b,
		bool case_sen) {
	bool equal_case_reversed = (
		(!case_sen) && char_is_alphabet(b) && a == char_case_switch(b)
	);
	return a == b || equal_case_reversed;
}

/** @brief Informa a quantidade de ocorrências de uma substring em uma string,
 *         considerando a capitalização ou não.
 *  @param string String em que a substring deve ser procurada.
 *  @param find Substring a ser procurada na string.
 *  @param case_sen Sensibilidade à capitalização.
 *  @return Quantidade de ocorrências de uma substring em uma string,
 *          considerando a capitalização ou não.
 */
int string_count(
		char *string,
		char *find,
		bool case_sen) {
	int str_len = string_length(string);
	int find_len = string_length(find);
	int find_count = 0;
	int match_idx = 0;
	bool find_fits = true;
	bool char_match = false;
	bool str_match = false;
	for (int str_idx = 0; find_fits && str_idx < str_len; str_idx++) {
		char_match = char_compare(string[str_idx], find[match_idx], case_sen);
		if (char_match) {
			if (match_idx == find_len - 1) {
				find_count++;
				str_match = true;
				if (str_idx + 1 + find_len > str_len)
					find_fits = false;
				}
			else
				match_idx++;
		}
		if (!char_match || str_match) {
			match_idx = 0;
			str_match = false;
		}
	}
	return find_count;
}

/** @brief Em uma string, susbstitui uma substring por outra substring.
 *  @param find Substring a ser procurada e substituida pela outra substring.
 *  @param replace Substring a ser inserida no lugar da substring find.
 *  @param case_sen Sensibilidade à capitalização.
 *  @return Ponteiro para uma cópia da string, com ocorrências da substring
 *          find substituídas pela substring replace.
 */
char *string_replace(
		char *string,
		char *find,
		char *replace,
		bool case_sen) {
	int find_cnt = string_count(string, find, case_sen);
	if (find_cnt > 0) {
		int string_len = string_length(string);
		int find_len = string_length(find);
		int replace_len = string_length(replace);
		int result_len = string_len + find_cnt * (replace_len - find_len);
		char *result = malloc((result_len + 1) * sizeof(char));
		int replaced_cnt = 0, match_idx = 0;
		int str_idx, res_idx;
		bool char_match;
		for (str_idx = 0; string[str_idx] != '\0'; str_idx++) {
			char_match = (
				char_compare(string[str_idx + match_idx], find[match_idx], case_sen)
			);
			while (find_cnt - replaced_cnt > 0 && char_match) {
				match_idx++;
				char_match = (
				char_compare(string[str_idx + match_idx], find[match_idx], case_sen)
				);
			}
			bool str_match = match_idx == find_len;
			if (str_match) {
				for (int rep_idx = 0; rep_idx < replace_len; rep_idx++) {
					res_idx = (str_idx - replaced_cnt * (find_len - replace_len));
					result[res_idx + rep_idx] = replace[rep_idx];
				}
				replaced_cnt++;
				str_idx += find_len;
			}
			res_idx = (str_idx - replaced_cnt * (find_len - replace_len));
			result[res_idx] = string[str_idx];
			match_idx = 0;
		}
		result[str_idx - replaced_cnt * (find_len - replace_len)] = '\0';
		free(string);
		return result;
	}
	return string;
}

/** @brief Transforma uma string em lowercase.
 *  @param string String a ser transformada em lowercase.
 */
void string_to_lower(char *string) {
	for (int i = 0; i < string_length(string); i++)
		if(char_is_upper(string[i]))
			string[i] = char_case_switch(string[i]);
}

/** @brief Remove números à direita de uma string.
 *  @param string String a ser tratada pela função.
 */
void string_remove_trailing_numbers(char *string) {
	int i = string_length(string) - 1;
	while (string[i] >= 48 && string[i] <= 57)
		i--;
	string[i+1] = '\0';
}

/** @brief Gera uma represa com nome e dados sobre seus níveis medidos em
 *         determinado dia.
 *  @param name Nome da represa.
 *  @param lvl_max Capacidade máxima da represa.
 *  @param lvl_cnt Quantidade de medidas de níveis no dia.
 *  @param lvls Níveis medidos no dia.
 *  @return A represa gerada, com o nome, os dados e a média dos níveis.
 */
Represa represa_set(
		char *name,
		float lvl_max,
		int lvl_cnt,
		int *lvls) {
	Represa represa;
	represa.name = string_copy(name);
	represa.lvl_max = lvl_max;
	represa.lvl_cnt = lvl_cnt;
	represa.lvl_avg = int_avg_truncated(lvls, lvl_cnt);
	represa.lvls = int_copy(lvls, lvl_cnt);
	return represa;
}

/** @brief Informa se o alerta de nível da represa deve ser acionado, ou seja,
 *         se algum nível medido no dia é maior que 90% do nível máximo da
 *         represa.
 *  @param represa A represa cujos níveis devem ser analisados.
 *  @return Se o alerta for acionado, retorna 1. Caso contrário, retorna 0.
 */
int represa_alert(Represa represa) {
	for (int i = 0; i < represa.lvl_cnt; i++)
		if (represa.lvls[i] >= 0.9 * represa.lvl_max)
			return 1;
	return 0;
}

/** @brief Imprime as informações de uma represa.
 *  @param represa A represa cujos dados devem ser impressos.
 */
void represa_print(Represa represa) {
	printf("NOME: %s\n", represa.name);
	printf("QTD NIVEIS: %d\n", represa.lvl_cnt);
	printf("MEDIA: %d\n", represa.lvl_avg);
	if (represa_alert(represa))
		printf("CAPACIDADE ACIMA DE 90%% DA MAXIMA!\n");
	printf("#####\n");
}

/** @brief Corrige nomes de represas, ou seja, remove o prefixo "represa_de_",
 *         troca underscores por espaços, transforma em lowercase e remove
 *         números à direita.
 *  @param represas Represas cujos nomes devem ser corrigidos.
 *  @param represas_cnt Quantidade de represas no vetor de represa.
 */
void represas_name_fix(
		Represa *represas,
		int represas_cnt) {
	for (int rep_idx = 0; rep_idx < represas_cnt; rep_idx++) {
		char *name_no_prefix = (
			string_replace(represas[rep_idx].name, "represa_de_", "", false)
		);
		represas[rep_idx].name = string_copy(name_no_prefix);
		free(name_no_prefix);
		char *name_with_spaces = (
			string_replace(represas[rep_idx].name, "_", " ", false)
		);
		represas[rep_idx].name = string_copy(name_with_spaces);
		free(name_with_spaces);
		string_to_lower(represas[rep_idx].name);
		string_remove_trailing_numbers(represas[rep_idx].name);
	}
}
