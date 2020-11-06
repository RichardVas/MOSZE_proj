#!/bin/bash

IFS=$'\n'

rm -f output.txt

echo `scenario1.json` >> $2
echo `scenario2.json` >> $2
