#!/bin/bash
if [ -e msg.txt ]
then
a=`cat msg.txt | aspell -d pl -a | grep '^*' | wc -l`

if [ $a = 1 ]
then
	echo "Wyraz znajduje sie w slowniku j.polskiego"
else
	echo "Wyraz nie znajduje sie w slowniku j.polskiego"
fi
rm msg.txt
fi
