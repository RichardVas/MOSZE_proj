#!/bin/bash

IFS=$'\n'


echo "$(cppcheck *.cpp --enable=warning --output-file=cppcheck_errors.txt)"
	if  [ ! -s .cppcheck_errors.txt ]
	then
			echo "No performance or style error."
			 echo "$(cppcheck *.cpp --enable=performance,style --output-file=cppcheck_performance.txt)"
		
		if [ ! -s cppcheck_performance.txt ]
		then
			echo "No performance or style error."
		fi
	else
			echo "Error/warning!"
			exit 1
	fi 
  
  
