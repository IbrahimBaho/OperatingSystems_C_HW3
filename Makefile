all: cthread

cthread: threads.c
	gcc -o cthread threads.c -pthread -lm

