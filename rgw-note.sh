
yum install mime* -y
radosgw -c ./ceph.conf -f -n client.rgw.ceph-rgw0


#s3cmd: port :8000
#set ~/.s3cfg use_https=False
