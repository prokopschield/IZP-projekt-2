#include <stdio.h>

void pipecmd(char* restrict command, FILE* f) {
	FILE *p = popen(command, "r");
	register char c;
	while ((c = fgetc(p)) != EOF) {
		fputc(c, f);
	}
}

int main() {
	FILE *setcal = fopen("setcal.c", "w");
	fprintf(setcal, "/* set calculator by { xkrama07, xpekni01, xschie03, xstipe02 } */\n");
	fprintf(setcal, "/* https://cdn.nodesite.eu/static/");
	pipecmd("node store", setcal);
	fprintf(setcal, ".html */\n");
	fprintf(setcal, "\n");
	pipecmd("node combine", setcal);
	fclose(setcal);
	pipecmd("gcc -std=c99 -pedantic -Wall -Wextra -Wformat -Werror -g -o setcal setcal.c", stdout);
}
