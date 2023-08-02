#!/bin/bash

output=$1
dev=$2

num_threads=4

db_home1=/home/root/nvme/db1
db_home2=/home/root/nvme/db2
db_home3=/home/root/nvme/db3
db_home4=/home/root/nvme/db4

mkdir -p $db_home1
mkdir -p $db_home2
mkdir -p $db_home3
mkdir -p $db_home4

# iostat log 
rm -f ${output}.iostat
iostat -xm 1 $dev > ${output}.iostat &
iostat_pid=$!

# issue print command
./issue_print.sh $dev &
issue_pid=$!

# cosmos uart log
sudo rm -f ${output}.uart
sudo cat /dev/ttyUSB0 > ${output}.uart &
cat_pid=$!

# blktrace 
sudo rm -rf ${output}.btrace
sudo btrace $dev > ${output}.btrace &
btrace_pid=$!
datasize=$((67108864))

if true
then

sudo ./db_bench -benchmarks=fillrandom -block_size=$((16*1024)) \
  -write_buffer_size=$((datasize)) -writable_file_max_buffer_size=$((datasize)) \
  -min_write_buffer_number_to_merge=2 -max_bytes_for_level_base=$((datasize)) \
	-target_file_size_base=$((datasize)) -max_bytes_for_level_multiplier=10 \
	-use_direct_io_for_flush_and_compaction=false -max_background_flushes=16 -use_direct_reads=false \
	-max_background_compactions=4 -duration=900 -histogram=true -use_stderr_info_logger=true \
  -report_file="${output}_report1.csv" -report_interval_seconds=10 \
	-value_size=1024 -db=$db_home1 -disable_wal -block_align=true \
	-compression_type=none   \
	-report_bg_io_stats -threads=$num_threads \
	--level0_file_num_compaction_trigger=2 2>&1 &> ${output}.log1 &

sudo ./db_bench -benchmarks=fillrandom -block_size=$((16*1024)) \
  -write_buffer_size=$((datasize)) -writable_file_max_buffer_size=$((datasize)) \
  -min_write_buffer_number_to_merge=2 -max_bytes_for_level_base=$((datasize)) \
	-target_file_size_base=$((datasize)) -max_bytes_for_level_multiplier=10 \
	-use_direct_io_for_flush_and_compaction=false -max_background_flushes=16 -use_direct_reads=false \
	-max_background_compactions=4 -duration=900 -histogram=true -use_stderr_info_logger=true \
  -report_file="${output}_report2.csv" -report_interval_seconds=10 \
	-value_size=1024 -db=$db_home2 -disable_wal -block_align=true \
	-compression_type=none   \
	-report_bg_io_stats -threads=$num_threads \
	--level0_file_num_compaction_trigger=2 2>&1 &> ${output}.log2 &

sudo ./db_bench -benchmarks=fillrandom -block_size=$((16*1024)) \
  -write_buffer_size=$((datasize)) -writable_file_max_buffer_size=$((datasize)) \
  -min_write_buffer_number_to_merge=2 -max_bytes_for_level_base=$((datasize)) \
	-target_file_size_base=$((datasize)) -max_bytes_for_level_multiplier=10 \
	-use_direct_io_for_flush_and_compaction=false -max_background_flushes=16 -use_direct_reads=false \
	-max_background_compactions=4 -duration=900 -histogram=true -use_stderr_info_logger=true \
  -report_file="${output}_report3.csv" -report_interval_seconds=10 \
	-value_size=1024 -db=$db_home3 -disable_wal -block_align=true \
	-compression_type=none   \
	-report_bg_io_stats -threads=$num_threads \
	--level0_file_num_compaction_trigger=2 2>&1 &> ${output}.log3 &

sudo ./db_bench -benchmarks=fillrandom -block_size=$((16*1024)) \
  -write_buffer_size=$((datasize)) -writable_file_max_buffer_size=$((datasize)) \
  -min_write_buffer_number_to_merge=2 -max_bytes_for_level_base=$((datasize)) \
	-target_file_size_base=$((datasize)) -max_bytes_for_level_multiplier=10 \
	-use_direct_io_for_flush_and_compaction=false -max_background_flushes=16 -use_direct_reads=false \
	-max_background_compactions=4 -duration=900 -histogram=true -use_stderr_info_logger=true \
  -report_file="${output}_report4.csv" -report_interval_seconds=10 \
	-value_size=1024 -db=$db_home4 -disable_wal -block_align=true \
	-compression_type=none   \
	-report_bg_io_stats -threads=$num_threads \
	--level0_file_num_compaction_trigger=2 2>&1 | tee ${output}.log4

fi

echo "[INFO] TEST FINISHED!"
sudo kill -9 `jobs -p` $iostat_pid $issue_pid $cat_pid $btrace_pid
