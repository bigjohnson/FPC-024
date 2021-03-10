#!/bin/bash
cc devport.c -o devport
echo You need root privileges to enable cap_sys_rawio on devport
sudo /sbin/setcap cap_sys_rawio=ep devport
