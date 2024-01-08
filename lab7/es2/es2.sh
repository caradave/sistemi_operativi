# !/bin/bash

clear

if test $# -ne 1
then
    echo "passati un numero sbagliato di argomenti"
    exit 1
fi

max=0
i=0

while read line
do
    if test ${#line} -gt $max
    then
        max=${#line}
    fi
    i=$((i+1))
done < $1

echo "$max"
echo "$i"
exit 0