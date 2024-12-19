#!/bin/bash

# important!! first call must have '-b' option
./docker_ctl.sh -b -s -c 'cd  /esp-idf && . ./export.sh && cd /workspace/ip_camera && idf.py build'
