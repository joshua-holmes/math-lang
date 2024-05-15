CC = clang

all: run-example

compile: src/main.c
	@$(CC) src/*.c -o main

run-example: compile main
	@./main example.do
	@rm ./main

