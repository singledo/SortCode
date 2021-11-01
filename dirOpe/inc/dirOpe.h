#ifndef _dirOpe_h
#define _dirOpe_h
#include "com.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define FULLPATHLEN_MAX (512)

#define COPE_PRESIZE (4*1024)

bool isExist (char *path);
bool isFile (char *path);
bool isDir (char *path);

#define ISDIR(x)   isDir(x)
#define ISFILE(x)  isFile(x)
#define ISExIST(x) isExist(x)


bool file2Dir (char *srcFile, char *dstDir);
bool file2File (char *src, char *dst);
bool dir2Dir (char *srcDir, char *dstDir);
bool delDir (char *dir);

#endif
