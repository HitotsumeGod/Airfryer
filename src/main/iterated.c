#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "airf.h"

void iterate_dir(char *op, char *parentd) {

	WIN32_FIND_DATA wd;
	HANDLE winhandle;
	char *namebuf, dirbuf[200];
	int n;
	bool have_recursed;
	
	if ((winhandle = FindFirstFile("*", &wd)) == INVALID_HANDLE_VALUE) {
		perror("findfirstfile err");
		exit(EXIT_FAILURE);
	}
	while (FindNextFile(winhandle, &wd) > 0) {
		have_recursed = false;
		if ((namebuf = malloc(sizeof(char) * (strlen(wd.cFileName) + 1))) == NULL) {
			perror("malloc err");
			exit(EXIT_FAILURE);
		}
		for (n = 0; n < strlen(wd.cFileName); n++)
			*(namebuf + n) = *(wd.cFileName + n);
		*(namebuf + n) = '\0';
			
		//IF A DIRECTORY IS ENCOUNTERED, RECURSIVELY ITERATE THROUGHOUT IT (SHOULD EVENTUALLY BE UPDATED TO USE THREADS FOR MULTICORE ADVANTAGE)
		if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (strcmp(".", namebuf) != 0 && strcmp("..", namebuf) != 0) {
				if (GetCurrentDirectory(sizeof dirbuf, dirbuf) == 0) {
					perror("getcurrentdir err");
					exit(EXIT_FAILURE);
				}
				if (SetCurrentDirectory(wd.cFileName) == 0) {
					perror("setdirectory err");
					exit(EXIT_FAILURE);
				}
				printf("Moving to %s from %s\n", namebuf, dirbuf);
				iterate_dir(op, dirbuf);
				have_recursed = true;
			}
		} else if (!(wd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN || wd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) && strcmp(THISNAME, namebuf) == 1) {
			if (strcmp("-e", op) == 0)
				fencrypt(wd.cFileName);
			else if (strcmp("-d", op) == 0)
				fdecrypt(wd.cFileName);
			else {
				printf("%s\n", "Invalid program argument.");
				exit(EXIT_FAILURE);
			}
		}
		free(namebuf);
		//RETURN TO PRIOR DIRECTORY IF RECURSIVE CALL
		if (have_recursed) {
			if (SetCurrentDirectory(parentd) == 0) {
				perror("setdirectory err");
				exit(EXIT_FAILURE);
			}
			printf("Returning to %s\n", parentd);
		}
	}
	if (GetLastError() != ERROR_NO_MORE_FILES) {
		perror("FindNextFile error.");
		exit(EXIT_FAILURE);
	}
		

}
