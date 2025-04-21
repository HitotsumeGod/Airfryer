#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "airf.h"

int main(int argc, char *argv[]) {

	char toexec[50];

	if (argc > 2) {
		return EXIT_FAILURE;
	}
	if (argc == 1) 
		iterate_dir("-e", argv[0]);
	else {
		sprintf(toexec, "%s %s", argv[0], argv[1]);
		iterate_dir(argv[1], toexec);
	}

	return 0;

}
