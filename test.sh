#!/bin/bash

IFS=$'\n'

rm -f output.txt

echo `./main scenario1.json` >> $2
echo `./main scenario2.json` >> $2

