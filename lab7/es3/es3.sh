# !/bin/bash

for f in $(find *)
do
    upperCase=$(tr [:lower:] [:upper:] <<< $f)
    upperCase2=$(echo $f | tr a-z A-Z)
    echo $upperCase
    echo $upperCase2
done

exit 0