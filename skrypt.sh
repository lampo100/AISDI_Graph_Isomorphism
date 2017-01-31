#!/bin/sh
i=0
j=1
k=2
while [ $i -lt 10 ]
do
python gen.py Graph$j Graph$k
./GraphIsomorphism Graph$j Graph$k
i=`expr $i + 1`
j=`expr $j + 2`
k=`expr $k + 2`
sleep 2
done
