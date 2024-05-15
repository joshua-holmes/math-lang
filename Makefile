CC = clang
OUT = do-lang

all: run-example

compile: src/main.c
	@$(CC) src/*.c -o $(OUT)

run-example: compile
	@./$(OUT) example.do
	@rm ./$(OUT)

