#!/bin/bash

counter=1
while [[ $counter -le $1 ]]
do
	if [[ $counter -gt 0 ]]
	then		
		./dining-p $1 $counter &
	fi
	((counter++))
done 
