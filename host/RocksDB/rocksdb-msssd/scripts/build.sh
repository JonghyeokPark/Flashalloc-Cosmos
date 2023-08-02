#!/bin/bash

if [ -z "$1" ]
then
  echo "cosmos"
	DEBUG_LEVEL=0 CXX=g++ make -j7 db_bench EXTRA_CXXFLAGS='-DCOSMOS_DEV=\"/dev/nvme1n1\"'  -B
  mv db_bench vanilla
else
  echo "use sallocate"
	DEBUG_LEVEL=0 CXX=g++ make -j7 db_bench EXTRA_CXXFLAGS='-DUSE_SALLOCATE=1 -DCOSMOS_DEV=\"/dev/nvme1n1\" -w'  -B
fi
