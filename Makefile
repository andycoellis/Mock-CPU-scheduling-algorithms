.default: all

all: run

fcfs:
	./run input/processes-3.txt

sjf:
	./run input/processes-3.txt -s

rr:
	./run input/processes-3.txt -r

clean: 
	rm -rf main *.o *.dSYM

run: main.o queue.o FCFS.o SJF.o RR.o
		gcc -Wall -Werror -g -O -o $@ $^

%.o: %.c
	gcc -Wall -Werror -g -O -c $^

build:
	gcc -Wall -O -o run *.c