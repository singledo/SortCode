
# fast way to cd target directory
f ()
{
	M4=imx-m4-firmware/
	OpenSource=vendor/nxp-opensource/
	img=out/target/product/mek_8q
	UUU=uuu/
	QNXPre=/home/z/workspace/QNX-Space/qnxSource
	qnxSrc=src/hardware
	qnxUUU=images/emmc/imx8-uuu
	

	# echo "cd fast version"                                 
	case $1 in                                             
		m)                                                                                       
			cd $ProjectPre
			;;                                                               
		o)
			cd  ${ProjectPre}${OpenSource}
			;;
		m4)                                                   
			cd ${ProjectPre}${OpenSource}${M4}
			;;                         
		img)                      
			cd ${ProjectPre}${img}
			;;                                                                                            
		u)
			cd ${WorkSpace}${UUU}
			;;
		cam)
			cd $CAMARE                                                                                    
			;;                                                                                            
		note):
			cd /home/z/Nutstore\ Files
			;;
		qnx)
			cd ${QNXPre}
			;;
		qsrc)
			cd ${QNXPre}${qnxSrc}
			;;
		qu)
			cd ${QNXPre}${qnxUUU}
			;;
		*)        
			echo "Badly aegument"                                                                         
			;;                                                                                            
	esac 
}

Mount()
{
	remoteDir=/home/danny/i8QM/imx-p9.0.0_2.1.1-auto-ga/android_buil
	localDir=/home/z/workspace/IMX8QM-Andoird/source

	case $1 in
		a)
			# fusermount -u ${localDir}
			/home/z/workspace/bin/mountAndoird
			;;
		rm)
			sudo fusermount -u ${localDir}
			;;
		*)
			echo "wrong argument"
			;;
	esac
}

# ctags and cscopr
# -C mean clean
# -b mean build

Sync()
{
	case $1 in
		-b)
			sudo ctags -R .
			sudo cscope -Rbq
			;;
		-c)
			sudo rm tags
			sudo rm cscope.in.out cscope.out cscope.po.out
			;;
	esac
}

vpn()
{
	echo "dash board url: http://clash.razord.top/#/settings"
	sudo  /home/z/workspace/bin/clash/clash-linux-amd64 -d /home/z/workspace/bin/clash
}

AcquirePrefix()
{
	data=$(</home/z/workspace/bin/pre.cfg)
	#return $data
	echo $data
}

AndPre()
{
	echo $1/ > /home/z/workspace/bin/pre.cfg
	source ~/.bashrc
}


IMX8ENV()
{
	export ARCH=arm64
	export CROSS_COMPILE=/home/z/workspace/IMX8QM-Andoird/android_build/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
	export ARMGCC_DIR=/home/z/workspace/IMX8QM-Andoird/android_build/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/
}

proxy ()
{
	export ALL_PROXY=socks5://127.0.0.1:7890
	export https_proxy=http://127.0.0.1:7890
	export http_proxy=http://127.0.0.1:7890
	export all_proxy=socks5://127.0.0.1:7891

# git config --global https.proxy http://127.0.0.1:7890
# git config --global https.proxy https://127.0.0.1:7891
	git config --global http.proxy 'socks5://127.0.0.1:7890' 
	git config --global https.proxy 'socks5://127.0.0.1:7891'
}

unproxy ()
{
	unset ALL_PROXY="socks5://127.0.0.1:7890"
	unset https_proxy="http://127.0.0.1:7890"
	unset http_proxy="http://127.0.0.1:7890"
	unset all_proxy="socks5://127.0.0.1:7891"

# git config --global https.proxy http://127.0.0.1:7890
# git config --global https.proxy https://127.0.0.1:7891
	git config --global --unset http.proxy
	git config --global --unset https.proxy
}

