CODE=copy.c
OUTPUT=copy
debug:
	gcc -O1 src/$(CODE) -o build/debug/$(OUTPUT) -g
	./build/debug/$(OUTPUT)
prod:
	gcc -O2 src/$(CODE) -o build/prod/$(OUTPUT)
