
# fast way to cd target directory
f ()
{
	M4=imx-m4-firmware/
	OpenSource=vendor/nxp-opensource/
	img=out/target/product/mek_8q
	UUU=uuu/

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
		bm4)                                                                 
			cd ${ProjectPre}${OpenSource}${}
			;;                                                                       
		image)                      
			cd ${ProjectPre}${img}
			;;                                                                                            
		u)
			cd ${WorkSpace}${UUU}
			;;
		cam):                                                                                 
			cd $CAMARE                                                                                    
			;;                                                                                            
		*)        
			echo "Badly aegument"                                                                         
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
			ctags -R .
			cscope -Rbq
			;;
		-c)
			rm tags
			rm cscope.in.out cscope.out cscope.po.out
			;;
	esac
}

vpn()
{
	echo "dash board url: http://clash.razord.top/#/settings"
	sudo  /home/z/workspace/bin/clash/clash-linux-amd64 -d /home/z/workspace/bin/clash
}


