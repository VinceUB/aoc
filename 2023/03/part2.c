#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int value;
	bool checked;
} Number;

typedef enum {
	BLANK=0, GEAR, NUMBER
} SquareType;

typedef struct {
	SquareType type;
	Number* number;
} Square;


typedef struct {
	int width;
	int height;
	Square** squares; //This is gonna be (y, x), for the sake of easier reallocation (probs)
	int parts_total;
} Grid;

void grid_new_line(Grid* g){
	//There's probably a smarter way than reallocating every time:)
	Square** new_ptr;
	new_ptr = reallocarray(g->squares, ++g->height, sizeof(Square*));
	
	if(new_ptr){
		g->squares = new_ptr;
	} else {
		fprintf(stderr, "Could not allocate new grid line %d", g->height);
	}

	g->squares[g->height-1] = calloc(g->width, sizeof(Square));
}

//Returns {BLANK, NULL} if out of range
Square grid_access(Grid g, int y, int x){
	if(y<0 || x<0 || y>=g.height || x>=g.width)
		return (Square){BLANK, NULL};
	else
		return g.squares[y][x];
}
	
//For the first passthrough
void grid_put(Grid* g, int y, int x, int value){ //I probably don't really need `g` to be a pointer here
	switch(value){
		case '\r': case '\n':
			fprintf(stderr, "Ya doofus, you were supposed to filter the newlines out!");
			exit(-1);
			break;
		case '0': case '1': case '2': case '3': case '4': 
		case '5': case '6': case '7': case '8': case '9': 
			g->squares[y][x].type = NUMBER;

			if(grid_access(*g, y, x-1).type==NUMBER){
				g->squares[y][x].number = grid_access(*g, y, x-1).number;
				g->squares[y][x].number->value *= 10;
				g->squares[y][x].number->value += value-'0';
			} else {
				g->squares[y][x].number = malloc(1 * sizeof(Number));
				g->squares[y][x].number->value = value-'0';
				g->squares[y][x].number->checked = false;
			}
			break;
		case '*':
			g->squares[y][x].type = GEAR;
			//We don't add any totals until second passthrough,
			//because some of the numbers haven't been read yet
			break;
		default:
			g->squares[y][x] = (Square){BLANK, NULL};
			break;
	}
}

//For the second passthrough
void passthrough_2(Grid* g, int y, int x){
	Square s = grid_access(*g, y, x);
	
	if(s.type != GEAR)
		return;

	
	Square to_check[] = {
		grid_access(*g,y-1,x-1),grid_access(*g,y-1,x  ),grid_access(*g,y-1,x+1),
		grid_access(*g,y  ,x-1),                        grid_access(*g,y  ,x+1),
		grid_access(*g,y+1,x-1),grid_access(*g,y+1,x  ),grid_access(*g,y+1,x+1)
	};

	Number to_multiply[2];
	int n = 0; //To see if there's one or two numbers next to the gear

	for(int i = 0; i < sizeof(to_check)/sizeof(to_check[0]); i++){
		if(to_check[i].type == NUMBER && !to_check[i].number->checked){
			if(n<2) to_multiply[n] = *(to_check[i].number);
			n++;

			to_check[i].number->checked = true;
		}
	}

	if(n==2)
		g->parts_total += to_multiply[0].value * to_multiply[1].value;

	//Uncheck all numbers we checked
	for(int i = 0; i < sizeof(to_check)/sizeof(to_check[0]); i++)
		if (to_check[i].type==NUMBER)
			to_check[i].number->checked = false;
}

int main(int argc, char** argv){
	Grid g = {0, 0, NULL, 0};

	FILE* f = fopen(argv[1], "r");

	//Zeroth passthrough, get width
	int i,c;	
	for(i=0; c!=EOF && c!='\n' && c!='\r'; i++ & (c=getc(f)));
	fseek(f, SEEK_SET, 0);
	g.width = i-1;
	
	//First passthrough, initialise grid
	int y = 0;
	int x = 0;
	
	grid_new_line(&g);
	while((c=getc(f))!=EOF){
		switch(c){
			case '\r':
				break;
			case '\n':
				grid_new_line(&g);
				y++;
				x = 0;
				break;
			default:
				grid_put(&g, y, x, c);
				x++;
				break;
		}
	}
	fseek(f, SEEK_SET, 0);

	y = 0;
	x = 0;
	
	while((c=getc(f))!=EOF){
		switch(c){
			case '\r':
				break;
			case '\n':
				y++;
				x = 0;
				break;
			default:
				passthrough_2(&g, y, x);
				x++;
				break;
		}
	}

	printf("The engine total is %d\n", g.parts_total);
}
