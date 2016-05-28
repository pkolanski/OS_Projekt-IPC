#!/bin/bash

make receive
make send
./send
./receive
./check.sh
make clean
