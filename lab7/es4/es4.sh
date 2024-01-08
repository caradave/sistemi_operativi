#!/bin/bash

clear

if [ $# -ne 1 ]; then
    echo "Inserisci il nome del file: "
    read fileName
else
    fileName=$1
fi

textContent=$(cat "$fileName")

declare -a parole
declare -a occorrenze
newWord=0

for word in $textContent; do
    check=0
    
    for ((i=0; i<${#parole[*]}; i++)); do
        if [ "$word" == "${parole[$i]}" ]; then
            check=1
            ((occorrenze[$i]++))
        fi
    done

    if [ $check -eq 0 ]; then
        parole[$newWord]=$word
        occorrenze[$newWord]=1
        ((newWord++))
    fi
done

for ((i=0; i<${#parole[*]}; i++)); do
    echo "${parole[$i]}: ${occorrenze[$i]}"
done

exit 0
