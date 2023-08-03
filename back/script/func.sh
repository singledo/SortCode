# script by zhangjun 

# fast jump the work directory
j ()
{
	PROJECT_PRE=/opt/jzhang91/workspace/visteon_work/jmc_cs
	ANDROID_PRE=${PROJECT_PRE}/aosp-caf
	MODIFY_PRE=${PROJECT_PRE}/programs/jmc/my2024/p789

	case $1 in 
		a|and)
			cd  ${ANDROID_PRE}
			;;
		w|work)
			cd ${PROJECT_PRE}
			;;
		m|modify)
			cd ${MODIFY_PRE}
			;;
		q|qnx)
			cd  ${MODIFY_PRE}/snapdragon-auto-gen3-hqx-1-2-1_hlos_dev_qnx/P789
			;;
		sq|s_qnx)
			cd  ${MODIFY_PRE}/snapdragon-auto-gen3/snapdragon-auto-gen3-hqx-1-2-1_hlos_dev_qnx/apps/qnx_ap
			;;
		m|modify)
			cd ${MODIFY_PRE}
			;;
		*)
			echo "unkonow argument for j function"
			;;
	esac
}

start_tmux ()
{
	echo "start home page"
}

dock_env ()
{
	source ~/bin/dockenv_jmc.sh
}

up_db()
{
	cur_dir=${PWD}

	dbfile_list=(cscope.in.out  cscope.list cscope.out cscope.po.out  tags)

	for item in ${dbfile_list[@]}
	do
		if [ -f ${cur_dir}/${item} ]; then
			rm ${cur_dir}/${item}
		fi
	done

	find ${cur_dir} -name "*.h" -o -name "*.hpp" -o -name "*.c" -o -name "*.cpp" -o -name "*.cc" > ${cur_dir}/cscope.list
	cscope -bkq -i ${cur_dir}/cscope.list
	ctags -R ${cur_dir}

	if [ -f ${cur_dir}/cscope.list ]; then
		rm ${cur_dir}/cscope.list
	fi

	echo "update cscope database and ctags database compelete "
}

b_driver ()
{
	cur_dir=${PWD}
	echo "build driver ${cur_dir}---- start  "

	#tar=/opt/jzhang91/workspace/visteon_work/jmc_cs/aosp-caf/kernel/msm-5.4/drivers/misc/pcm6240
	tar=${PWD}

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

}
