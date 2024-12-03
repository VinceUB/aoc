#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum State{
	SN,                // Stable no-state
	N1,N2,N3,          // Reading `do()`
	SY,                // Stable yes-state
	M1,M2,M3,M4,       // Reading mul(
	N11,N12,N13,       // Reading first number
	C,                 // Comma
	N21,N22,N23,       // Reading second number
	Y1,Y2,Y3,Y4,Y5,Y6, // Reading `don't()`
	WRITE
};

const char* state_string[] = {
	"SN", "N1", "N2", "N3",
	"SY", "M1", "M2", "M3", "M4",
	"N11", "N12", "N13", "C", "N21", "N22", "N23",
	"Y1", "Y2", "Y3", "Y4", "Y5", "Y6",
	"WRITE"
};

const enum State start = SY;

enum State transition(enum State state, char symbol){
	switch(state){
		case SN:
			if(symbol=='d')
				return N1;
			else
				return SN;
		case N1:
			if(symbol=='o')
				return N2;
			else
				return SN;
		case N2:
			if(symbol=='(')
				return N3;
			else
				return SN;
		case N3:
			if(symbol==')')
				return SY;
			else
				return SN;

		case SY:
			//RESET HERE
			if(symbol=='m')
				return M1;
			else if(symbol=='d')
				return Y1;
			else
				return SY;
		case M1:
			if(symbol=='u')
				return M2;
			else
				return SY;
		case M2:
			if(symbol=='l')
				return M3;
			else
				return SY;
		case M3:
			if(symbol=='(')
				return M4;
			else
				return SY;
		case M4:
			if(symbol>='0' && symbol<='9')
				return N11;
			else
				return SY;
		case N11:
			if(symbol>='0' && symbol<='9')
				return N12;
			else if (symbol==',')
				return C;
			else
				return SY;
		case N12:
			if(symbol>='0' && symbol<='9')
				return N13;
			else if (symbol==',')
				return C;
			else
				return SY;
		case N13:
			if(symbol==',')
				return C;
			else
				return SY;
		case C:
			if(symbol>='0' && symbol<='9')
				return N21;
			else
				return SY;
		case N21:
			if(symbol>='0' && symbol<='9')
				return N22;
			else if (symbol==')')
				return WRITE;
			else
				return SY;
		case N22:
			if(symbol>='0' && symbol<='9')
				return N23;
			else if(symbol==')')
				return WRITE;
			else
				return SY;
		case N23:
			if(symbol==')')
				return WRITE;
			else
				return SY;

		case Y1:
			if(symbol=='m')
				return M1;
			else if (symbol=='o')
				return Y2;
			else
				return SY;
		case Y2:
			if(symbol=='m')
				return M1;
			else if (symbol=='n')
				return Y3;
			else
				return SY;
		case Y3:
			if(symbol=='m')
				return M1;
			else if (symbol=='\'')
				return Y4;
			else
				return SY;
		case Y4:
			if(symbol=='m')
				return M1;
			else if (symbol=='t')
				return Y5;
			else
				return SY;
		case Y5:
			if(symbol=='m')
				return M1;
			else if (symbol=='(')
				return Y6;
			else
				return SY;
		case Y6:
			if(symbol=='m')
				return M1;
			else if (symbol==')')
				return SN;
			else
				return SY;
		case WRITE:
			fprintf(stderr, "ERROR: Write's supposed to epsilon away\n");
			exit(-1);
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
#define LOG(n, ...) if(logging>=n) fprintf(stderr, __VA_ARGS__);

	int c;
	enum State state = start;
	char* num1 = calloc(4, 1);
	char* num2 = calloc(4, 1);
	int total = 0;

	while((c=getchar())!=EOF){
		state = transition(state, c);
		LOG(1, "%c", c);
		LOG(2, "%s", state_string[state]);
		switch(state){
			case SY:
				free(num1);
				num1 = calloc(4, 1);
				free(num2);
				num2 = calloc(4, 1);
				break;
			case N11:
				num1[0] = c;
				break;
			case N12:
				num1[1] = c;
				break;
			case N13:
				num1[2] = c;
				break;
			case N21:
				num2[0] = c;
				break;
			case N22:
				num2[1] = c;
				break;
			case N23:
				num2[2] = c;
				break;
			case WRITE:
				LOG(1, "\n%d*%d\n", atoi(num1), atoi(num2));
				total += atoi(num1) * atoi(num2);
				state = SY;

				free(num1);
				num1 = calloc(4, 1);
				free(num2);
				num2 = calloc(4, 1);

				break;
		}
	}
	printf("\n\nAnswer:%d\n", total);
}
