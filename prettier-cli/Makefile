SRC=prettier-cli.c
OUTPUT=prettier-cli

debug:
	gcc -O1 src/$(SRC) -o build/debug/$(OUTPUT) -g

prod:
	gcc -O2 src/$(SRC) -o build/prod/$(OUTPUT)
