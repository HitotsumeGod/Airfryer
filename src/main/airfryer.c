#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "airf.h"

int main(int argc, char *argv[]) {

	if (argc > 2) {
		return EXIT_FAILURE;
	}
	if (argc == 1) 
		iterate_dir("-e", argv[0]);
	else {
		if (strcat(argv[0], " ") == NULL) {
			perror("strcat err");
			return EXIT_FAILURE;
		}
		if (strcat(argv[0], argv[1]) == NULL) {
			perror("strcat err");
			return EXIT_FAILURE;
		}
		iterate_dir(argv[1], argv[0]);
	}

	return 0;

}
