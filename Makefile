CC = clang
OUT = mang

all: run-example

compile: src/main.c
	@$(CC) src/*.c -o $(OUT)

compile-debug: src/main.c
	@$(CC) src/*.c -o $(OUT) -g

run-example: compile
	@./$(OUT) example.do
	@rm ./$(OUT)

