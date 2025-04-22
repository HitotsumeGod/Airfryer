#include <stdio.h>
#include <stdlib.h>
#include "airf.h"

void fencrypt(char *fname) {

	FILE *f;
	char *bitbuf;
	long fsize;

	if ((f = fopen(fname, "rb")) == NULL) {
		fprintf(stderr, "%s%s\n", fname, " is under lock and key.");
		return;
	}
	if (fseek(f, 0, SEEK_END) == -1) {
		perror("fseek err");
		exit(EXIT_FAILURE);
	}
	fsize = ftell(f);
	rewind(f);
	if ((bitbuf = malloc(sizeof(char) * fsize)) == NULL) {
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	if (fread(bitbuf, sizeof(char), fsize, f) < 0) 
		if (ferror(f)) {
			perror("fread err");
			exit(EXIT_FAILURE);
		}
	for (int i = 0; i < fsize; i++) {
		if (*(bitbuf + i) < ASCII_LIM - DEGREE)
			*(bitbuf + i) += DEGREE;
		else 
			*(bitbuf + i) -= DEGREE;
	}
	if (freopen(fname, "wb", f) == NULL) {
		fprintf(stderr, "%s%s\n", fname, " is under lock and key.");
		free(bitbuf);
		return;
	}
	printf("%s %s.\n", "Encrypting", fname);
	if (fwrite(bitbuf, sizeof(char), fsize, f) < 0) {
		perror("fwrite err");
		exit(EXIT_FAILURE);
	}
	if (fclose(f) == -1) {
		perror("fclose err");
		exit(EXIT_FAILURE);
	}
	free(bitbuf);

}
