#!/bin/bash

echo "$(cppcheck *.cpp --enable=warning --output-file=warnings.txt)"

if [-s ./warnings.txt]
then
    echo "Errors/Warnings found! -> log: warnings.txt"
    exit 1

else
    echo "$(cppcheck *.cpp --enable=style --output-file=warning_style.txt)"
    if [-s ./warning_style.txt]
    then 
        echo "Style problems -> log: warning_style.txt"
    fi

    echo "$(cppcheck *.cpp --enable=performance --output-file=warning_perform.txt)"
    if [-s ./warning_perform.txt]
    then 
        echo "Performance problems -> log: warning_perform.txt"
    fi
fi
