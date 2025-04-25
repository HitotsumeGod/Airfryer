#include <stdio.h>
#include <windows.h>
#include <aclapi.h>
#include "winkit.h"

bool erase_file_dacl(char *fname) {

	if (SetNamedSecurityInfo(
				fname,
				SE_FILE_OBJECT,
				DACL_SECURITY_INFORMATION,
				NULL,
				NULL,
				NULL,
				NULL
	) != ERROR_SUCCESS) 
		return false;
	printf("%s\n", "dacl erased!!");
	return true;

}
