// Quick and dirty way to convert brainfuck to wysi

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	if(argc != 2 && argc != 3) {
		printf("Usage: %s<in.bf> [out.wysi]\n", argv[0]);
		return 0;
	}

	FILE* in = fopen(argv[1], "r");
	if(in == NULL) {
		printf("Failed to open input file\n");
		return 1;
	}

	FILE* out;
	if(argc == 2) { // Pretty sure there is a better way to do this
		char fname[strlen(argv[1] + 6)];
		strcpy(fname, argv[1]);
		strcat(fname, ".wysi");
		out = fopen(fname, "w");
	}
	else
		out = fopen(argv[2], "w");

	if(out == NULL) {
		fclose(in);
		printf("Failed to open output file\n"); // w
		return 1;
	}

	int chr;
	while(!feof(in)) {
		chr = getc(in);
		switch(chr) {
			case '>':
				fprintf(out, "when ");
				break;
			case '<':
				fprintf(out, "you ");
				break;
			case '+':
				fprintf(out, "almost ");
				break;
			case '-':
				fprintf(out, "see ");
				break;
			case '.':
				fprintf(out, "it ");
				break;
			case ',':
				fprintf(out, "shige ");
				break;
			case '[':
				fprintf(out, "727 ");
				break;
			case ']':
				fprintf(out, "wysi ");
				break;
			//default: // Let's actually ignore all comments and stuff
		}
	}

	fclose(in);
	fclose(out);
	return 0;
}
