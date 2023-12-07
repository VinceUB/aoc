a.out: hand_checkers.c part2.c
	gcc -g -o a.out hand_checkers.c part2.c

all: a.out

run-real: a.out
	./a.out input

run-test: a.out
	./a.out test-input

debug: a.out
	lldb a.out -- input

debug-test: a.out
	lldb a.out -- test-input
