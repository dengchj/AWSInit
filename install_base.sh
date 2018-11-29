#! /usr/bin/bash

yum install git gcc gcc-c++ cmake mime* perf ctags -y
systemctl stop firewalld
systemctl status firewalld
setenforce 0
getenforce
