#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum State{
	A,B,C,D,E, //mul(
	F,G,H,I, //xxx,
	J,K,L,M //xxx)
};

const enum State accept = M;
const enum State start = A;

enum State transition(enum State state, char symbol){
	switch(state){
		case A:
			if(symbol=='m')
				return B;
			else
				return A;
		case B:
			if(symbol=='u')
				return C;
			else
				return A;
		case C:
			if(symbol=='l')
				return D;
			else
				return A;
		case D:
			if(symbol=='(')
				return E;
			else
				return A;
		case E:
			if(symbol>='0' && symbol<='9')
				return F;
			else
				return A;
		case F:
			if(symbol>='0' && symbol<='9')
				return G;
			else if (symbol==',')
				return I;
			else
				return A;
		case G:
			if(symbol>='0' && symbol<='9')
				return H;
			else if (symbol==',')
				return I;
			else
				return A;
		case H:
			if(symbol==',')
				return I;
			else
				return A;
		case I:
			if(symbol>='0' && symbol<='9')
				return J;
			else
				return A;
		case J:
			if(symbol>='0' && symbol<='9')
				return K;
			else if (symbol==')')
				return M;
			else
				return A;
		case K:
			if(symbol>='0' && symbol<='9')
				return L;
			else if (symbol==')')
				return M;
			else
				return A;
		case L:
			if(symbol==')')
				return M;
			else
				return A;
		case M:
			fprintf(stderr, "Attempting to advance from accept state");
		default:
			fprintf(stderr, "ERROR\n");
			exit(-1);
	}
}



int main(int argc, char** argv){
	int logging = 0;
	if(argc<=1)
		logging = 0;
	else if (!strcmp(argv[1], "+"))
		logging = 1;
	else if (!strcmp(argv[1], "++"))
		logging = 2;

	int c;
	enum State state = start;
	char* num1 = calloc(4, 1);
	char* num2 = calloc(4, 1);
	int total = 0;

	while((c=getchar())!=EOF){
		state = transition(state, c);
		if(logging > 0)
			fprintf(stderr, "%c", c);
		if(logging > 1)
			fprintf(stderr, "%c", state+'A');
		switch(state){
			case A:
				free(num1);
				num1 = calloc(4, 1);
				free(num2);
				num2 = calloc(4, 1);
				break;
			case F:
				num1[0] = c;
				break;
			case G:
				num1[1] = c;
				break;
			case H:
				num1[2] = c;
				break;
			case J:
				num2[0] = c;
				break;
			case K:
				num2[1] = c;
				break;
			case L:
				num2[2] = c;
				break;
			case M:
				if(logging > 0)
					fprintf(stderr, "\n%d*%d\n", atoi(num1), atoi(num2));
				total += atoi(num1) * atoi(num2);
				state = A;
				free(num1);
				num1 = calloc(4, 1);
				free(num2);
				num2 = calloc(4, 1);
				break;
		}
	}
	printf("\n\nAnswer:%d\n", total);
}
