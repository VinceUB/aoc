#include <stdio.h>
#include <stdlib.h>

struct System {
	struct {
		int (*println)(int);
	} out;
};

int custom_print(int i){
	printf("%d", i);
}
struct System System = {{&custom_print}};

int cmp(const void* a, const void* b){
	return *(int*)a-*(int*)b;}

int main(){
	int input_length = 0;
	int* left = 0;
	int* right = 0;
	
	for(char* line = calloc(1, 1000000); fgets(line, 10000, stdin)!=NULL;)
		(left=realloc(left, 4*(++input_length))),(right=realloc(right, 4*input_length)),
			sscanf(line, "%d %d", left+input_length-1, right+input_length-1);

	qsort(left, input_length, 4, &cmp);
	qsort(right, input_length, 4, &cmp);

	int distances = 0;
	for(int i = 0; i<input_length; i++){
#include <math.h>
		distances += abs(left[i]-right[i]);
	}

	System.out.println(distances);
	puts("");
}
