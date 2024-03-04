local:
	gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o example 1-6.c -lm
	valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./example
	rm example

docker:
	docker build --tag example .
	docker run -v "$(CURDIR)":/1-6 example
	docker rmi example 
