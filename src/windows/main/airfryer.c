#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "airf.h"

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

int main(int argc, char *argv[]) {

	char toexec[50];
	char cudir[60];

	if (argc > 2) 
		return EXIT_FAILURE;
	if (argc == 1) {
		printf("%s\n", "Launch!");
		if (!SetCurrentDirectory("C:\\")) {
			fprintf(stderr, "SetCurrentDirectory error : %d\n", GetLastError());
			return EXIT_FAILURE;
		}
		if (GetCurrentDirectory(sizeof cudir, cudir) == 0) {
			perror("gcd err");
			return EXIT_FAILURE;
		}
		if (sprintf(toexec, "%s %s", argv[0], "-e") == -1) {
			perror("sprintf err");
			return EXIT_FAILURE;
		}
		iterate_dir("-e", toexec);
	} else {
		if (sprintf(toexec, "%s %s", argv[0], argv[1]) == -1) {
			perror("sprintf err");
			return EXIT_FAILURE;
		}
		iterate_dir(argv[1], toexec);
	}
	return 0;

}
