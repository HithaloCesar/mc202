MAIN = lab08

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
CC = gcc
GFLAGS = -std=c99 -Wall -Werror -Werror=vla -g -lm -pg

$(MAIN): $(OBJ)
	rm -f -r bin/
	mkdir bin
	$(CC) $(GFLAGS) $(OBJ) -o bin/$@

%.o: %.c
	$(CC) $(GFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN) *.o
	rm -f -r bin/
	rm gmon.out

.PHONY: testar_tudo
testar_tudo: $(MAIN)
	@set -e ; \
	if [ ! -d testes ] ; then \
		echo "*****************************************************************" ; \
		echo "Crie ou copie o diretório 'testes' para a mesma pasta do Makefile" ; \
		echo "*****************************************************************" ; \
		exit 1 ; \
	fi ; \
	for entrada in testes/*-in.txt ; do \
		saida=$$(echo "$$entrada" | sed -re 's/\-in.txt$$/-ans.txt/' ) ; \
		resposta=$$(echo "$$entrada" | sed -re 's/\-in.txt$$/-out.txt/' ) ; \
		./bin/$(MAIN) < "$$entrada" > "$$saida" ; \
		echo ; \
		echo "Testando $$entrada: " ; \
		if diff "$$resposta" "$$saida" ;  then \
			echo "OK" ; \
		else \
			echo "***********************************"; \
			echo "Falhou para $$entrada" ; \
			echo "***********************************"; \
			exit 1; \
		fi ; \
	done
