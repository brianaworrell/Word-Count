#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[]){
	if((argc > 2)|(argc < 2)){
		printf("Error: Expected one argument.");
		return 0;
	}
	const char* filename = argv[1];
	/*printf("%s",filename);*/
	int file = open(filename, O_RDONLY);
	if (file == -1){
		printf("Error: file does not exist.");
		return 0;
	}
	int chars = 0;
	int words = 0;
	int lines = 0;

	char a[1];
	int returnval = 1;
	int prev = 10;
	while (returnval ==1){
		returnval = read(file, a, 1);
		if (returnval == -1){
			printf("Error: file cannot be read.");
			return 0;
		}
		else if (returnval == 0){
			if (prev == 10){
				/*printf("Error: file is empty.");
				return 0;*/
			}
			else if (prev != 5){
				lines = lines + 1;
			}
		}
		else if (isalnum(a[0])){
			chars = chars + 1;
			if  ((prev == 10)||(prev==2)||(prev==3)||(prev==5)){
				words = words + 1;
			}
			prev = 1;
		}
		else if (a[0] == '\n'){
			lines = lines + 1;
			chars = chars + 1;
			prev = 5;
		}
		else if (ispunct(a[0])){
			chars = chars + 1;
			if  ((prev == 10)||(prev==2)||(prev==3)||(prev==5)){
                                words = words + 1;
                        }
			prev = 4;
		}
		else if (isspace(a[0])){
			chars = chars + 1;
			prev = 2;
		}
		else if (iscntrl(a[0])){
			chars = chars + 1;
			prev = 3;
			printf("check1");
			if (a[0] == '\n'){
				lines = lines + 1;
				prev = 5;
				printf("check2");
			}
		}
	}
	printf ("%i %i %i %s\n", lines, words, chars, filename);
	return 0;
}
