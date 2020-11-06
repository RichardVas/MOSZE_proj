#!/bin/bash

rm -f output.txt

./a.out units/scenario1.json >>curr_output1.txt
.a .out units/scenario2.json >>curr_output2.txt

diff --strip-trailing-cr curr_output1.txt output1.txt
diff --strip-trailing-cr curr_output2.txt output2.txt

if [ $? -eq 0 ]
then
echo "No differences. The test was OK!"
else
echo "Test failed."
fi

