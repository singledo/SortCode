#!/bin/bash

AOSP_PRJ=/opt/jzhang91/workspace/visteon_work/jmc_p789/jmc_es1/aosp-caf
ARCH=arm64 
CROSS_COMPILE=$AOSP_PRJ/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android- 
OUT=$AOSP_PRJ/out/target/product/msmnile_gvmq/obj/kernel/msm-5.4
REAL_CC=$AOSP_PRJ/prebuilts/clang/host/linux-x86/clang-r383902/bin/clang 
CLANG_TRIPLE=aarch64-linux-gnu- 
AR=$AOSP_PRJ/prebuilts/clang/host/linux-x86/clang-r383902/bin/llvm-ar 
LLVM_NM=$AOSP_PRJ/prebuilts/clang/host/linux-x86/clang-r383902/bin/llvm-nm 
LD=$AOSP_PRJ/prebuilts/clang/host/linux-x86/clang-r383902/bin/ld.lld 
NM=$AOSP_PRJ/prebuilts/clang/host/linux-x86/clang-r383902/bin/llvm-nm 
DTC_EXT=$AOSP_PRJ/out/host/linux-x86/bin/dtc 
DTC_OVERLAY_TEST_EXT=$AOSP_PRJ/out/host/linux-x86/bin/ufdt_apply_overlay 
CONFIG_BUILD_ARM64_DT_OVERLAY=y 
HOSTCC=$AOSP_PRJ/prebuilts/clang/host/linux-x86/clang-r383902b1/bin/clang 
HOSTAR=$AOSP_PRJ/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-ar 
HOSTLD=$AOSP_PRJ/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-ld 

KERNEL_DIR=$AOSP_PRJ/kernel/msm-5.4

$AOSP_PRJ/prebuilts/build-tools/linux-x86/bin/make -C $KERNEL_DIR  ARCH=$ARCH CROSS_COMPILE=$CROSS_COMPILE \
'HOSTCFLAGS=-I/opt/jzhang91/workspace/visteon_work/jmc_p789/jmc_es1/aosp-caf/kernel/msm-5.4/include/uapi  -I/opt/jzhang91/workspace/visteon_work/jmc_p789/jmc_es1/aosp-caf/kernel/msm-5.4/include -L/usr/lib -L/usr/lib/x86_64-linux-gnu -fuse-ld=lld' \
'HOSTLDFLAGS=-L/usr/lib -L/usr/lib/x86_64-linux-gnu -fuse-ld=lld'  O=$OUT REAL_CC=$REAL_CC CLANG_TRIPLE=$CLANG_TRIPLE AR=$AR LLVM_NM=$LLVM_NM LD=$LD NM=$NM \
	DTC_EXT=$DTC_EXT DTC_OVERLAY_TEST_EXT=$DTC_OVERLAY_TEST_EXT CONFIG_BUILD_ARM64_DT_OVERLAY=y  HOSTCC=$HOSTCC HOSTAR=$HOSTAR HOSTLD=$HOSTLD  -j 72

