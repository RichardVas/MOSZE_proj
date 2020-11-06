#!/bin/bash

IFS=$'\n'
echo "$(valgrind --leak-check=yes --log-file=valgrind_check.txt ./main scenario1.json)"
valgrind_check_result="$(cat ./valgrind_check.txt)"
echo $valgrind_check_result
check_errors="$(echo $valgrind_check_result | sed 's/^.*ERROR SUMMARY: \([0-9]*\) errors.*$/\1/')"
if [ "$check_errors" == "0" ]
then
    echo "No memory leaks!"
else
    echo "Memory leaks!"
    exit 1
fi
