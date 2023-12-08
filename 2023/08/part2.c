#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	char s[3];
	char l[3];
	char r[3];
} Element;

Element* all;

Element* element(char c[3]){
	return &all[(c[0]-'A') + (c[1]-'A')*26 + (c[2]-'A')*26*26];
}


Element next(Element e, char direction){
	if(direction=='L')
		return *element(e.l);
	else
		return *element(e.r);
}

bool all_z(int ac, Element* av){
	for(int i = 0; i < ac; i++)
		if(av[i].s[2]!='Z')
			return false;
	return true;
}

int main(int argc, char** argv){
	all = calloc(26*26*26, sizeof(Element));

	FILE* f = fopen(argv[1], "r");

	char* dirv = malloc(1000);
	fgets(dirv, 999, f);
	int dirc = strlen(dirv);
	
	char* the_void = malloc(1000);
	fgets(the_void, 999, f);
	free(the_void);
	
	Element* av = malloc(1000 * sizeof(Element)); //There cannot be more than 1000 A's, sorry
	int ac = 0;	

	char* line = malloc(1000);

	puts("Starting to read");
	while(fgets(line, 999, f)){
		char s[] = {line[ 0], line[ 1], line[ 2]};

		Element* e = element(s);
		
		*e = (Element){ (char[3]){0, 0, 0}, (char[3]){0, 0, 0}, (char[3]){0, 0, 0} };

		memcpy(e->s, s, 3);
		memcpy(e->l, line+7, 3);
		memcpy(e->r, line+12, 3);

		if(s[2]=='A')
			av[ac++] = *e;

		printf("%.3s = (%.3s, %.3s)\n", e->s, e->l, e->r);
	}
	puts("Finished reading");
	long long int i;
	for(i = 0; !all_z(ac, av); i++){
		for(int j = 0; j < ac; j++)
			av[j] = next(av[j], dirv[i%(dirc-1)]);
		
		if(i%100000000==0)
			printf("%10lld million\n", i/1000000);
	}

	printf("Took %lld iterations\n", i);
	
	return -1;
}
