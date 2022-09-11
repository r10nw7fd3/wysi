#include <stdio.h>
#include <string.h>

#define BUF_SIZE 48 // Max word length + 1, such a big buffer will allow us to create comments
#define ARRAY_SIZE 64 // It should actually be 30 000 but that's too much
#define LOOPSTACK_SIZE 16

char array[ARRAY_SIZE];
int ap = 0;

long loopstack[LOOPSTACK_SIZE];
int lp = 0;
int loop_skip = 0;
int comment_skip = 0; // Allows comments to be nested

void loopstack_push(long x) {
	loopstack[lp++] = x;
}

long loopstack_pop() {
	return loopstack[--lp];
}

long getword(char* buf, int max, FILE* fp) {
	int chr = getc(fp);
	// Skip white space
	while(chr == ' ' || chr == '\t' || chr == '\n')
		chr = getc(fp);
	ungetc(chr, fp);

	long pos = ftell(fp);
	chr = 0;
	for(int i = 0; i < max && (chr = getc(fp)) != ' ' && chr != '\t' && chr != '\n' && chr != EOF; i++)
		buf[i] = chr;

	return pos;
}

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Usage: %s <file.wysi>\n", argv[0]);
		return 1;
	}

	memset(array, 0, ARRAY_SIZE);

	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("Failed to open %s\n", argv[1]);
		return 2;
	}

	char word[BUF_SIZE];
	long loc;
	while(!feof(fp)) {
		memset(word, 0, BUF_SIZE);
		loc = getword(word, BUF_SIZE, fp);
		if(!strcmp(word, "when") && !loop_skip && !comment_skip) {
			if(ap >= ARRAY_SIZE - 1) {
				printf("Array pointer is out of bounds\n");
				return 3;
			}
			ap++;
		}
		else if(!strcmp(word, "you") && !loop_skip && !comment_skip) {
			if(ap <= 0) {
				printf("Array pointer is out of bounds\n");
				return 3;
			}
			ap--;
		}
		else if(!strcmp(word, "almost") && !loop_skip && !comment_skip) {
			array[ap]++;
		}
		else if(!strcmp(word, "see") && !loop_skip && !comment_skip) {
			array[ap]--;
		}
		else if(!strcmp(word, "it") && !loop_skip && !comment_skip) {
			putchar(array[ap]);
		}
		else if(!strcmp(word, "shige") && !loop_skip && !comment_skip) {
			array[ap] = getchar();
		}
		else if(!strcmp(word, "727") && !comment_skip) {
			if(lp >= LOOPSTACK_SIZE) {
				printf("Loop stack is full\n");
				return 3;
			}
			if(array[ap] && !loop_skip)
				loopstack_push(loc);
			else
				loop_skip++;
			
		}
		else if(!strcmp(word, "wysi") && !comment_skip) {
			if(loop_skip) {
				loop_skip--;
				continue;
			}
			if(!lp) {
				printf("Loop stack is empty\n");
				return 3;
			}
			fseek(fp, loopstack_pop(), SEEK_SET);
		}
		else if(!strcmp(word, "[["))
			comment_skip++;
		else if(!strcmp(word, "]]")) {
			if(!comment_skip) {
				printf("No comment section to close\n");
				return 3;
			}
			comment_skip--;
		}
		else if(*word /* EOF */ && !loop_skip && !comment_skip) {
			printf("Unknown instruction: %s\n", word);
		}
	}

	fclose(fp);
	return 0;
}
