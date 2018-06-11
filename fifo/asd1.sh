#!/bin/bash

if [ $# -eq 2 ]; then 
	szo=$1
	katalogus=$2
	szcj=0
	szco=0
	ssz=0
	s=$(find "$2" -type f -exec file {} \; | grep text | cut -d: -f1)
	for i in $s; do
		a=$(grep $1 $i -wo | wc -l)
		sorok=$(grep $1 $i)
		szcj=$a;
		szco=$(($szcj+$szco))
		ssz=$(($ssz+1))
		echo "$ssz - $i - $szcj"
		if [ $a -ne 0 ]; then
			echo -e "\n A sorok: \n$sorok\n"		
		fi	
	done
	echo "Elofordulasok szama osszesen: $szco"
else
	echo -e "Helyes hasznalat: $0 <keresett szo> <katalogus>"
fi

