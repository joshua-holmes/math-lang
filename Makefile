CC = clang
OUT = mang

all:
	@echo 'Welcome! See below for the cool dev commands you can use with this makefile'
	@echo 'make <command>'
	@echo "Commands:"
	@echo -e "\tcompile        # compiles the compiler and places executable in root project dir as ./mang"
	@echo -e "\tcompile-debug  # compiles compiler with debug symbols"
	@echo -e "\trun-example    # compiles the compiler then compiles and runs the example in example.mang using the mang compiler"

compile: src/main.c
	@$(CC) src/*.c -o $(OUT)

compile-debug: src/main.c
	@$(CC) src/*.c -o $(OUT) -g

run-example: compile
	@echo "Compiling example..."
	@./$(OUT) example.mang --output example
	@echo "Running example..."
	@./example

