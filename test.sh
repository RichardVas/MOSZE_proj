#!/bin/bash

IFS=$'\n'

rm output.txt

echo `./units scenario1.json` >> $2
echo `./units scenario2.json` >> $2
