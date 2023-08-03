 #/bin/bash

AND_PRE=/opt/jzhang91/workspace/visteon_work/jmc_p789/jmc_es1/aosp-caf
KERNEL_OUT=out/target/product/msmnile_gvmq/obj/kernel/msm-5.4
TAR=/opt/jzhang91/workspace/visteon_work/jmc_p789/jmc_es1/aosp-caf/kernel/msm-5.4/drivers/i2c/tusb4020
_CC=${AND_PRE}/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
_RC=${AND_PRE}/prebuilts/clang/host/linux-x86/clang-r383902/bin/clang
_AR=${AND_PRE}/prebuilts/clang/host/linux-x86/clang-r383902/bin/llvm-ar
_LN=${AND_PRE}/prebuilts/clang/host/linux-x86/clang-r383902/bin/llvm-nm 
_LD=${AND_PRE}/prebuilts/clang/host/linux-x86/clang-r383902/bin/ld.lld 
_NM=${AND_PRE}/prebuilts/clang/host/linux-x86/clang-r383902/bin/llvm-nm

make -j36 -C $AND_PRE/$KERNEL_OUT M=$TAR ARCH=arm64 \
    CROSS_COMPILE=$_CC REAL_CC=$_RC CLANG_TRIPLE=aarch64-linux-gnu- AR=$_AR LLVM_NM=$_LN LD=$_LD   NM=$_NM