#!/bin/bash

echo "SETUP Cosmos+ Board Start"
BLKDEV="/dev/nvme1n1"

 echo -e "d\n \n n\n \n \n \n \n w\n" | sudo fdisk $BLKDEV
 echo -e "y" | sudo mkfs.ext4 ${BLKDEV}p1
 sudo mount ${BLKDEV}p1 -odiscard /home/root/nvme
 sudo chmod 777 /home/root/nvme
 sudo mount | grep nvme

 echo "SETUP Cosmos+ Board Finish!"
