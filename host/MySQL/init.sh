#!/bin/bash

DATA_DIR=/path/to/data
echo "Initialize Database"
sudo ./bld/scripts/mysql_install_db --datadir=${DATA_DIR}
