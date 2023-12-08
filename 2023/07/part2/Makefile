a.out: hand_checkers.c part2.c
	cc -g -o a.out hand_checkers.c part2.c

all: a.out

run: a.out
	./a.out ../input

test: a.out
	./a.out ../test-input

debug: a.out
	lldb a.out -- ../input

debug-test: a.out
	lldb a.out -- ../test-input
