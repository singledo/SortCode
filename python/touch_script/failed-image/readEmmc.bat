@echo off

if "%~7" == "" (
    echo "aurgument number not true"
) else (
    echo "xxx"
)


set _COM=%1
echo %1% ::com

set searchdir=%2
echo %2% ::search_path

set _label=%3
echo %3% ::sendimage

set _physical_partition_number=%4
echo %4% ::_start_sector

set _start_sector=%5
echo %5% ::_num_partition_sectors

set _num_partition_sectors=%6
echo %6% ::_type

set _type=%7
echo %7% ::_guid

set _guid=%8
echo %8% ::_guid


@echo on

"C:\Program Files (x86)\Qualcomm\QPST\bin\fh_loader.exe"^
 --port=\\.\%_COM% ^
 --search_path=%searchdir% ^
 --convertprogram2read ^
 --sendimage=%_physical_partition_number%_%_start_sector%_%_label%.bin ^
 --start_sector=%_start_sector% ^
 --lun=%_physical_partition_number% ^
 --num_sectors=%_num_partition_sectors% ^
 --noprompt --showpercentagecomplete --zlpawarehost=1 --memoryname=ufs 
