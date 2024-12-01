#include <stdio.h>
#include <stdlib.h>
int main(){
	int input_length = 0;
	int* left = 0;
	int* right = 0;
	
	for(char* line = calloc(1, 1000000); fgets(line, 10000, stdin)!=NULL;)
		(left=realloc(left, 4*(++input_length))),(right=realloc(right, 4*input_length)),
			sscanf(line, "%d %d", left+input_length-1, right+input_length-1);
	
	int similarity = 0;
	for(int l = 0; l< input_length; l++){
		int n = 0;
		for(int r = 0; r < input_length; r++){
			if(left[l]==right[r]) n++;
		}
		similarity += left[l]*n;	
	}
	printf("%d\n", similarity);
}
