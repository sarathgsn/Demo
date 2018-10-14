#!/bin/bash
array=("A" "B" "ElementC" "ElementE")
for element in "${array[@]}"
do
    echo "$element"
done

echo
echo "Number of elements: ${#array[@]}"
echo
echo "${array[@]}"
