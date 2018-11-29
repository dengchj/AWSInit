#!/bin/bash

../src/stop.sh
../src/vstart.sh -n --mon_num 1 --osd_num 3 --mds_num 1 --rgw_num 1

./bin/radosgw-admin user create --uid=user1 --access-key=user1 --secret=user1 --display-name="user1"

./bin/ceph auth get-or-create client.librgw osd 'allow rwx' mon 'allow rwx' -o /dist/UMStor-OS/build/client.librgw.keyring

echo -e "[client.librgw]\nkeyring = /dist/UMStor-OS/build/client.librgw.keyring" >> /dist/UMStor-OS/build/ceph.conf
