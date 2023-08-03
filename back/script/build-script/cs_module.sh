#!/bin/bash

tar=/opt/jzhang91/workspace/visteon_work/jmc_cs/aosp-caf/kernel/msm-5.4/drivers/misc/pcm6240
echo $tar
rm_list=(i2c-pcm6240.ko  i2c-pcm6240.lto.o  i2c-pcm6240.mod  i2c-pcm6240.mod.c  i2c-pcm6240.mod.o  i2c-pcm6240.o   modules.order  Module.symvers)

for node in ${rm_list[@]}
do
	if [ -f $tar/$node ]; then
		rm $tar/$node
	else
		echo "$node not exist"
	fi
done

AND_PRE=/opt/jzhang91/workspace/visteon_work/jmc_cs/aosp-caf
KERNEL_DIR=kernel/msm-5.4 
DEFCONFIG=vendor/autogvm-qgki-debug_defconfig 
OUT_DIR=out/target/product/msmnile_gvmq/obj/kernel/msm-5.4 
MAKE_PATH=$AND_PRE/prebuilts/build-tools/linux-x86/bin/ 
ARCH=arm64 
CROSS_COMPILE=$AND_PRE/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android- 
KERNEL_MODULES_OUT=out/target/product/msmnile_gvmq/dlkm/lib/modules 
KERNEL_HEADERS_INSTALL=out/target/product/msmnile_gvmq/obj/kernel/msm-5.4/usr 
HEADERS_INSTALL=0 
TARGET_PREBUILT_INT_KERNEL=out/target/product/msmnile_gvmq/obj/kernel/msm-5.4/arch/arm64/boot/Image 
TARGET_INCLUDES="\"-I$AND_PRE/kernel/msm-5.4/include/uapi -I/usr/include -I/usr/include/x86_64-linux-gnu -I/opt/jzhang91/workspace/visteon_work/jmc_cs/aosp-caf/kernel/msm-5.4/include -L/usr/lib -L/usr/lib/x86_64-linux-gnu -fuse-ld=lld\" "
TARGET_LINCLUDES="\"-L/usr/lib -L/usr/lib/x86_64-linux-gnu -fuse-ld=lld\""
VENDOR_KERNEL_MODULES_ARCHIVE=vendor_modules.zip 
VENDOR_RAMDISK_KERNEL_MODULES_ARCHIVE= 
VENDOR_RAMDISK_KERNEL_MODULES=\"\" 
REAL_CC=$AND_PRE/prebuilts/clang/host/linux-x86/clang-r383902b1/bin/clang 
CLANG_TRIPLE=aarch64-linux-gnu- 
AR=$AND_PRE/prebuilts/clang/host/linux-x86/clang-r383902b1/bin/llvm-ar 
LLVM_NM=$AND_PRE/prebuilts/clang/host/linux-x86/clang-r383902b1/bin/llvm-nm 
LD=$AND_PRE/prebuilts/clang/host/linux-x86/clang-r383902b1/bin/ld.lld 
NM=$AND_PRE/prebuilts/clang/host/linux-x86/clang-r383902b1/bin/llvm-nm 
DTC_EXT=$AND_PRE/out/host/linux-x86/bin/dtc 
DTC_OVERLAY_TEST_EXT=$AND_PRE/out/host/linux-x86/bin/ufdt_apply_overlay 
CONFIG_BUILD_ARM64_DT_OVERLAY=y 
HOSTCC=$AND_PRE/prebuilts/clang/host/linux-x86/clang-r383902b1/bin/clang 
HOSTAR=$AND_PRE/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-ar 
HOSTLD=$AND_PRE/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-ld
CFLAGS_MODULE=-fno-pic


${MAKE_PATH}make -j72 -C $AND_PRE/$OUT_DIR  M=$tar ARCH=${ARCH}  CROSS_COMPILE=${CROSS_COMPILE} REAL_CC=${REAL_CC} CLANG_TRIPLE=aarch64-linux-gnu- \
    AR=${AR} LLVM_NM=${LLVM_NM} LD=${LD} NM=${NM} HOSTCFLAGS="${TARGET_INCLUDES}" HOSTLDFLAGS="${TARGET_LINCLUDES}"  CFLAGS_MODULE=-fno-pic  -j${NCORES} modules


