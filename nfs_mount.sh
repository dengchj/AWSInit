echo "ONLY for nfs client and server in ONE node!"
echo "nfs ganesha..."
ganesha.nfsd -L /var/log/ganesha.log  -f /etc/ganesha/ganesha.conf
sleep 5
showmount -e localhost
echo "nfs client mount..."
umount /mnt
mount -t nfs -o noauto,noacl,soft,nfsvers=3,proto=tcp,nolock,sync 127.0.0.1:/ /mnt
sleep 3
mount -v
date
