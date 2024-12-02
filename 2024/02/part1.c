#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
				fprintf(stderr, ".%d ", numbers[n-1]);}
			else
				numbers[n] = 
					numbers[n]*10 
					+ (line[i] - '0');
		}
		fprintf(stderr, ".%d ", numbers[n-1]);
		fprintf(stderr, "\n");
		fflush(stderr);


		//Validate
		bool is_safe = true;
		int direction = -numbers[0]+numbers[1];
		for(int i = 1; i < n; i++){
			int diff = numbers[i]-numbers[i-1];
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
		//fprintf(stderr, "\n%s\t\tis %s\n", line, safe?"safe":"unsafe");
		if(is_safe){
			safe++;
		}
		fprintf(stderr, "\n\n");
	}
	printf("%d\n", safe);
}
