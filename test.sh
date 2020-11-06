#!/bin/bash

IFS=$'\n'

rm output.txt

echo `./main scenario1.json` >> $2
echo `./main scenario2.json` >> $2
