MAIN = lab09

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
	rm -f gmon.out

.PHONY: testar_tudo
testar_tudo: $(MAIN)
	@set -e ; \
	if [ ! -d ../../tests ] ; then \
		echo "********************************" ; \
		echo "Diretório 'tests' não existente." ; \
		echo "********************************" ; \
		exit 1 ; \
	fi ; \
	for entrada in ../../tests/*-in.txt ; do \
		saida=$$(echo "$$entrada" | sed -re 's/\-in.txt$$/-ans.txt/' ) ; \
		resposta=$$(echo "$$entrada" | sed -re 's/\-in.txt$$/-out.txt/' ) ; \
		./bin/$(MAIN) < "$$entrada" > "$$saida" ; \
		echo ; \
		echo "Testando $$entrada: " ; \
		if diff "$$resposta" "$$saida" ;  then \
			echo "OK" ; \
			rm -f tests/*-ans.txt ; \
		else \
			echo "***********************************"; \
			echo "Falhou para $$entrada" ; \
			echo "***********************************"; \
			exit 1; \
		fi ; \
	done
