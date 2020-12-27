#ifndef _log_h
#define _log_h

#include "com.h"
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



#define LOGPATHMAX (255)

int logInit (char *path);
int logInfo (char *fmt, ...);

#endif
