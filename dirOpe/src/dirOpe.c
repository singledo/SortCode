#include "dirOpe.h"

// call this after isExist
bool isDir (char *path)
{
	assert(path != NULL);
	struct stat statInof;
	int iRet = -1;

	iRet = stat(path, &statInof);
	if (-1 == iRet) {
		printf("[%s@%d],[%s]\n",__FUNCTION__,__LINE__, strerror(errno));
		return false;
	}
	if (0 == S_ISDIR (statInof.st_mode))
		return false;
	else
		return true;
}

bool isFile (char *path)
{
	assert(path != NULL);
	struct stat statInof;
	int iRet = -1;

	iRet = stat(path, &statInof);
	if (-1 == iRet) {
		printf("[%s@%d],[%s]\n",__FUNCTION__,__LINE__, strerror(errno));
		return false;
	}
	if (0 == S_ISREG (statInof.st_mode))
		return false;
	else
		return true;

	return true;
}

bool isExist (char *path)
{
	assert (path != NULL);
	if (-1 == access(path, F_OK))
		return false;
	else
		return true;
}




bool file2File (char *src, char *dst)
{
	int srcFd = -1 , dstFd = -1;
	int nRead = 0, nWrite = 0, nDone = 0;
	char *pBuf = NULL;
	mode_t oldMask;
    mode_t newMask ;

	/*newMask =  S_IRWXU | S_IRWXG | S_IRWXO; [> other read <]*/
	newMask =  0;
	oldMask = umask (newMask);

	pBuf = (char *) malloc(COPE_PRESIZE);
	if (NULL == pBuf) {
		return false;
	}

	if (isExist(src) == false) {
		return false;
	}

	srcFd = open (src, O_RDONLY);
	if (-1 == srcFd) {
		return false;
	}

	dstFd = open (dst, O_WRONLY | O_CREAT | O_TRUNC, \
				  S_IRWXU | S_IRWXG | S_IRWXO);
	if (-1 == dstFd) {
		return false;
	}
	memset (pBuf, 0, COPE_PRESIZE);

	while ((nRead = read(srcFd, pBuf, COPE_PRESIZE)) && \
		   (nRead > 0)) {

		nWrite = write (dstFd, pBuf, nRead);
		nDone = nWrite;
		while (nWrite < nRead) {
			nWrite = write (dstFd, pBuf+nDone, nRead-nDone);
			if (-1 == nWrite) {
				free (pBuf);
				close (srcFd);
				close (dstFd);
				return false;
			}
			nDone += nWrite;
		}
	}

	free (pBuf);
	close (srcFd);
	close (dstFd);
	umask (oldMask);

	return true;
}


bool file2Dir (char *srcFile, char *dstDir)
{
	char dstFullPath[FULLPATHLEN_MAX];
	char *pMark = NULL, *pLastMark = NULL;
	int dstPathLen = 0;

	assert (srcFile != NULL);
	assert (dstDir  != NULL);

	memset (dstFullPath, 0, FULLPATHLEN_MAX);


	if ((false == isExist (srcFile)) || \
		(false == isFile (srcFile)))
	{
		return false;
	}

	if (false == isExist(dstDir) || \
		(false == isDir(dstDir))){
		return false;
	}


	pMark = pLastMark = srcFile;
	while ((pMark = strstr(pMark+1, "/")) && \
		   (pMark != NULL)) {
		pLastMark = pMark;
	}
	pMark = pLastMark;

	dstPathLen = strlen(dstDir) + strlen(pMark) + 1;
	if (dstPathLen > FULLPATHLEN_MAX) {
		return false;
	}

	sprintf (dstFullPath, "%s/%s", dstDir, pMark+1);

	return file2File (srcFile, dstFullPath);
}


bool dir2Dir (char *srcDir, char *dstDir)
{

	assert (srcDir != NULL);
	assert (dstDir != NULL);
	char srcFullPath[FULLPATHLEN_MAX];
	char dstFullPath[FULLPATHLEN_MAX];
	int pathLen = 0;

	DIR *pDir = NULL;
	struct dirent *pDirInfo = NULL;
	bool bRet = true;


	pDir = opendir (srcDir);
	if (NULL == pDir) {
		return false;
	}

	while ((pDirInfo = readdir (pDir)) != NULL) {
		if (0 == memcmp (pDirInfo->d_name, ".", strlen(".")))
			continue;
		if (0 == memcmp (pDirInfo->d_name, "..", strlen("..")))
			continue;

		memset (srcFullPath, 0, FULLPATHLEN_MAX);
		sprintf (srcFullPath, "%s/%s", srcDir, pDirInfo->d_name);

		if (DT_DIR == (pDirInfo->d_type & DT_DIR)) {
			pathLen = strlen(pDirInfo->d_name) + strlen(srcDir) + 1;
			if (pathLen > FULLPATHLEN_MAX) {
				bRet = false;
				break;
			}

			pathLen = strlen(pDirInfo->d_name) + strlen(dstDir) + 1;
			if (pathLen > FULLPATHLEN_MAX) {
				bRet = false;
				break;
			}

			memset (dstFullPath, 0, FULLPATHLEN_MAX);
			sprintf (dstFullPath, "%s/%s", dstDir, pDirInfo->d_name);

			if (mkdir (dstFullPath,  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) == -1) {
				bRet = false;
				break;
			}

			bRet = dir2Dir (srcFullPath, dstFullPath);
		} else if(DT_REG == (pDirInfo->d_type & DT_REG)) {
			pathLen = strlen(pDirInfo->d_name) + strlen(srcDir) + 1;

			if (pathLen > FULLPATHLEN_MAX) {
				bRet = false;
				break;
			}
			bRet = file2Dir (srcFullPath, dstDir);
		}
		if (false == bRet) {
			break;
		}
	}
	closedir (pDir);
	return bRet;
}


bool delDir (char *dir)
{
	assert (dir != NULL);

	DIR *pDir = NULL;
	struct dirent *pDirInfo = NULL;
	bool bRet = true;
	int iRet = -1;
	bool bRes = true;

	char fullPath[FULLPATHLEN_MAX];

	if (false == isDir(dir)) {
		printf("[%s@%d],[%s]\n",__FUNCTION__,__LINE__, strerror(errno));
		return false;
	}
	pDir = opendir (dir);
	if (NULL == pDir) {
		printf("[%s@%d],[%s]\n",__FUNCTION__,__LINE__, strerror(errno));
		return false;
	}
	while ((pDirInfo = readdir (pDir)) && \
		   (pDirInfo != NULL)) {
		if (0 == memcmp (pDirInfo->d_name, ".", strlen("."))){
			continue;
		}
		if (0 == memcmp (pDirInfo->d_name, "..", strlen(".."))){
			continue;
		}

		memset (fullPath, 0, FULLPATHLEN_MAX);
		sprintf (fullPath, "%s/%s", dir, pDirInfo->d_name);

		if (DT_DIR == (pDirInfo->d_type & DT_DIR)) {
			bRet = delDir (fullPath);
			if (false == bRet) {
				printf("[%s@%d],[%s]\n",__FUNCTION__,__LINE__, strerror(errno));
				bRes = false;
				break;
			}
		} else {
			iRet = remove (fullPath);
			if (-1 == iRet) {
				printf("[%s@%d],[%s]\n",__FUNCTION__,__LINE__, strerror(errno));
				bRes = false;
				break;
			}
		}
	}
	closedir (pDir);
	iRet = remove (dir);
	if (-1 == iRet) {
		printf("[%s@%d],[%s]\n",__FUNCTION__,__LINE__, strerror(errno));
		bRes = false;
	}
	if (false == bRes) {
		return false;
	} else {
		return true;
	}
}
