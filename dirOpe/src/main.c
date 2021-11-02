#include "dirOpe.h"


int main (int argc, char *argv)
{
	printf ("dirOpe test Programe \n");
#if 0
	char srcFile[] = "/home/z/test/src/Windows.iso";
	char dstFile[] = "/home/z/test/dst/windows.iso";
	bool bRet = false;

	bRet = file2File (srcFile, dstFile);
	if (false == bRet) {
		printf ("copy %s to %s failed \n", srcFile, dstFile);
	} else {
		printf ("copy %s to %s success \n", srcFile, dstFile);
	}
#endif

#if 0
	char srcFile[] = "/home/z/test/src/Windows.iso";
	char dstDir[] = "/home/z/test/dst";
	bool bRet = false;

	bRet = file2Dir (srcFile, dstDir);
	if (false == bRet) {
		printf ("Dir Copy %s to %s failed \n", srcFile, dstDir);
	} else {
		printf ("Dir Copy %s to %s success \n", srcFile, dstDir);
	}
#endif

	char srcDir[] = "/home/z/workspace/Resource/toolchain/gcc-arm-none-eabi-7-2018-q2-update";
	char dstDir[] = "/home/z/workspace/dirOpeDst";
	bool bRet = false;

	bRet = dir2Dir (srcDir, dstDir);
	if (false == bRet) {
		printf ("DIR copy  %s to %s failed \n", srcDir, dstDir);
	} else {
		printf ("DIR copy  %s to %s success \n", srcDir, dstDir);
	}
#if 0
	char dir[] = "/home/z/test/dst";
	bool bRet = false;

	bRet = delDir (dir);
	if (false == bRet) {
		printf ("del dir [%s] failed \n", dir);
	} else {
		printf ("del dir [%s] success \n", dir);
	}
#endif



	return 0;
}
