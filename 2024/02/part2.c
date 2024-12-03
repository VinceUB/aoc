#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_safe(int numc, int* numv){
		bool is_safe = true;
		int direction = -numv[0]+numv[1];
		for(int i = 1; i < numc; i++){
			fprintf(stderr, "Got %d\n", numv[i]);
			int diff = numv[i]-numv[i-1];
			if( diff == 0){
				is_safe = false;
				fprintf(stderr, "unsafe because %d==0\n", diff);
			} else if (diff > 0 && direction < 0 ){
				is_safe = false;
				fprintf(stderr, "unsafe because %d>0 and direction is %d\n", diff, direction);
			} else if ( diff < 0 && direction > 0 ){
				is_safe = false;
				fprintf(stderr, "unsafe because %d<0 and direction is %d\n", diff, direction);
			} else if (abs(diff)>3){
				is_safe = false;
				fprintf(stderr, "unsafe because %d is more than 3\n", diff);
			}

		}
		return is_safe;
}

//Actually copies the thing
int* remove2(int* array, int length, int index){
	int* output = malloc(length*400-4);
	bool past_index = false;
	for(int i = 0; i < length; i++){
		fprintf(stderr, "\tIndex %d: %d\n", i, array[i]);
		if(i==index){
			fprintf(stderr, "\tSkipping\n");
			past_index = true;
			continue;
		} else
		output[past_index?i-1:i] = array[i];
	}
	fprintf(stderr, "\tDone\n");

	return output;
}

int main(){
	int safe = 0;

	char* line = calloc(1, 10000);
	while(fgets(line, 10000, stdin)!=NULL){
		//Read line in
		int* numbers = malloc(1000000000);
		int n = 0;
		for(int i = 0; i < strlen(line)+1; i++){
			if(line[i]==' ' || line[i]=='\n'){
				n++;
				fprintf(stderr, "%d, ", numbers[n-1]);}
			else
				numbers[n] = 
					numbers[n]*10 
					+ (line[i] - '0');
		}
		fprintf(stderr, "%d", numbers[n-1]);
		fprintf(stderr, "\n");
		fflush(stderr);

		//fprintf(stderr, "\n%s\t\tis %s\n", line, safe?"safe":"unsafe");
		if(is_safe(n, numbers)){
			safe++;
		} else {
			for(int i = 0; i < n; i++){
				fprintf(stderr, "Removing index %d\n", i);
				int* removed = remove2(numbers, n, i);
				if(is_safe(n-1, removed)){
					safe++;
					break;
				}
			}
		}
		fprintf(stderr, "\n\n");
	}
	printf("%d\n", safe);
}
