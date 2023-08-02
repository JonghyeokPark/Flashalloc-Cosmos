#!/bin/bash

#num_operation=$((100*1024*1024 / 4))
num_operation=$((1000*1024*1024 / 4))
num_threads=4
db_home=/home/root/nvme

output=$1
dev=$2

sudo rm -rf $db_home/*

#ulimit -Sn unlimited

# iostat
sudo rm -rf ${output}.iostat
iostat -xm 1 $dev > ${output}.iostat &
iostat_pid=$!

# print issue
./issue_print.sh $dev &
issue_pid=$!

# uart
sudo rm -rf ${output}.uart
sudo cat /dev/ttyUSB0 > ${output}.uart &
uart_pid=$!

datasize=$((67108864))

if true
then
sudo ./db_bench -benchmarks=fillrandom -block_size=$((16*1024)) \
	-target_file_size_base=$((datasize)) -max_bytes_for_level_multiplier=10 \
  -write_buffer_size=$((datasize)) -writable_file_max_buffer_size=$((datasize)) \
	-use_direct_io_for_flush_and_compaction=false -max_background_jobs=4 \
  -max_background_flushes=16 -use_direct_reads=false \
	-num=$num_operation -min_write_buffer_number_to_merge=2 \
	-value_size=1024 -db=$db_home -disable_wal -block_align=true \
	-compression_type=none \
  -report_file="${output}_report.csv" -report_interval_seconds=10 \
	-report_bg_io_stats -threads=$num_threads \
	--level0_file_num_compaction_trigger=2 | tee ${output}.log
fi

echo "[INFO] Test is finished!"
sudo kill -9 `jobs -p` $iostat_pid $issue_pid $uart_pid
