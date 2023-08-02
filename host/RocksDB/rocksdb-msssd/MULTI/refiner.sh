#!/bin/bash

#/home/csoyee/git/cosmos-msssdate-app/cosmos_plus_msssdate/refiner-1s/refiner fio \
#/home/csoyee/git/cosmos-msssdate-app/cosmos_plus_msssdate/refiner-1s/refiner fio \
#/home/csoyee/git/cosmos-msssdate-app/cosmos_plus_msssdate/refiner-10s/refiner fio \
/home/csoyee/git/cosmos-sallocate-app/refiner/refiner-60 fio \
    --waf1=msssd.uart --waf2=vanilla.uart \
    --iostat1=msssd.iostat --iostat2=vanilla.iostat
