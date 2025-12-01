#!/bin/bash

echo -n "Enter a string: "
read str

# Reverse the string
rev_str=$(echo "$str" | rev)

# Compare original and reversed
if [ "$str" = "$rev_str" ]; then
    echo "\"$str\" IS a palindrome"
else
    echo "\"$str\" is NOT a palindrome"
fi
