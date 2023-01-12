all: engi.o math.o eval.o
	${CC} -o engi.out engi.o eval.o math.o -lm
engi.o: engi.c eval.h
	${CC} -std=c99 -O3 -c engi.c
eval.o: eval.c eval.h
	${CC} -std=c99 -O3 -c eval.c
math.o: math.c
	${CC} -std=c99 -O3 -c math.c
install:
	mv engi.out /usr/local/bin/engicalc
