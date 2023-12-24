filename=input.txt
if [ ! -d "Result" ]; then
    mkdir "Result"
fi
while read line; do
    read x y operation <<< "$line"
    if [ "$operation" == "xor" ]; then
        result=$((x ^ y))
        echo "result of XOR $x and $y: $result" >> "Result/Output.txt"
    elif [ "$operation" == "product" ]; then
        result=$((x * y))
        echo "result of product $x and $y: $result" >> "Result/Output.txt"
    elif [ "$operation" == "compare" ]; then 
        if [ "$x" -gt "$y" ]; then 
        	result="$x"
            echo "result of compare $x $y: $result" >> "Result/Output.txt"
        elif [ "$y" -gt "$x" ]; then
        	result="$y"
            echo "result of compare $x $y: $result" >> "Result/Output.txt"
        else
            echo "$x $y are equal" >> "Result/Output.txt"
        fi
    fi
done < "$filename"



