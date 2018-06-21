#!/bin/bash

ftp -n -i 10.1.0.2 << EOF
user opendingux
pwd
cd /mmcblk0p1/local/home/emulators/dingux-msx
mput dingux-msx
bye
EOF
