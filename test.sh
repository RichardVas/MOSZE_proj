#!/bin/bash

IFS=$'\n'

rm -f output.txt

./a.out scenario1.json >> output.txt
./a.out scenario2.json >> output.txt
