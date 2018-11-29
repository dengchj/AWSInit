#!/bin/bash

nohup cp ./t1 /mnt/test/ftt1 1>/dist/txtout1 &
nohup cp ./t2 /mnt/test/ftt2 1>/dist/txtout2 &
nohup cp ./t3 /mnt/test/ftt3 1>/dist/txtout3 &
nohup cp ./t4 /mnt/test/ftt4 1>/dist/txtout4 &
sleep 7
nohup cp /mnt/test/tt1 ./tf1 1>./txt1 &
nohup cp /mnt/test/tt2 ./tf2 1>./txt2 &
nohup cp /mnt/test/tt3 ./tf3 1>./txt3 &
nohup cp /mnt/test/tt4 ./tf4 1>./txt4 &
