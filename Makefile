compile: src/main.c
	@gcc src/main.c -o main

run-example: src/main.c
	@make run-example && ./main example.do && rm ./main

