#include <stdio.h>
#include <stdlib.h>

#define WIDTH 1000
#define HEIGHT 1000

int actual_width, actual_height;

char** input;

char g(int y, int x){
	if(x<0 || y<0 || y>=actual_height || x>=actual_width)
		return '\0';
	else
		return input[y][x];
}

// This isn't necessary, I just forgot to put them all in quotes and 
// am too lazy to do so now
enum {
	X='X',M='M',A='A',S='S'
};


int xmasses(int y, int x){
	int tot=0;
	// XMAS
	if(g(y, x)==X 	&& g(y,  x+1)==M	&& g(y, x+2)==A 	&& g(y,  x+3)==S)
		tot++;
	
	// X
	//  M
	//   A
	//    S
	if(g(y,x)==X 	&& g(y+1,x+1)==M 	&& g(y+2,x+2)==A	&& g(y+3,x+3)==S)
		tot++;
	
	// X
	// M
	// A
	// S
	if(g(y,x)==X	&& g(y+1,x  )==M	&& g(y+2,x  )==A	&& g(y+3,x  )==S)
		tot++;

	//    X
	//   M
	//  A
	// S
	if(g(y,x)==X	&& g(y+1,x-1)==M	&& g(y+2,x-2)==A	&& g(y+3,x-3)==S)
		tot++;

	// SMAX
	if(g(y,x)==X	&& g(y  ,x-1)==M	&& g(y  ,x-2)==A	&& g(y  ,x-3)==S)
		tot++;

	// S
	//  A
	//   M
	//    X
	if(g(y,x)==X	&& g(y-1,x-1)==M	&& g(y-2,x-2)==A	&& g(y-3,x-3)==S)
		tot++;

	// S
	// A
	// M
	// X
	if(g(y,x)==X	&& g(y-1,x  )==M	&& g(y-2,x  )==A	&& g(y-3,x  )==S)
		tot++;

	//    S
	//   A
	//  M
	// X
	if(g(y,x)==X	&& g(y-1,x+1)==M	&& g(y-2,x+2)==A	&& g(y-3,x+3)==S)
		tot++;
	
	fprintf(stderr, "\033[4%dm%c\033[m", tot, g(y,x));
	return tot;
}

int main(){
	input = calloc(sizeof(char*), HEIGHT);

	for(int i = 0; i < HEIGHT; i++){
		input[i] = calloc(sizeof(char), WIDTH);
	}
	
	int c;
	int x = 0;
	int y = 0;
	while((c=getchar())!=EOF){
		fprintf(stderr,"%c",c);
		switch(c){
			case '\n':
				actual_width = x;
				x = 0;
				y++;
				break;
			default:
				input[y][x++] = c;
				break;
		}
	}
	actual_height = y;
	
	fprintf(stderr, "%d:%d, %d:%d\n", y, actual_height, x, actual_width);
	fprintf(stderr, "Key: ");
	for(int i = 0; i < 10; i++)
		fprintf(stderr, "\033[4%dm%d\033[m", i, i);
	fprintf(stderr, "\n");

	int tot = 0;
	for(y = 0; y < actual_height; y++){
		for(x = 0; x < actual_width; x++)
			tot += xmasses(y, x);
		fprintf(stderr, "\n");
	}
	printf("%d\n", tot);
}
