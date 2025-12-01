#!/bin/bash

echo -n "Enter a number: "
read num

# Handle numbers less than 2
if [ $num -lt 2 ]; then
    echo "$num is NOT a prime number"
    exit
fi

# Check for factors
is_prime=1   # Assume prime

for ((i=2; i*i<=num; i++))
do
    if (( num % i == 0 )); then
        is_prime=0
        break
    fi
done

# Output result
if [ $is_prime -eq 1 ]; then
    echo "$num IS a prime number"
else
    echo "$num is NOT a prime number"
fi
