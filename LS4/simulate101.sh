declare -a PRBLM_SIZES=("2000" "3000" "4000" "5000" "6000" "7000" "8000")
declare -a PG_FRM_SIZES=("16" "32" "64" "128" "256")
declare -a PG_FRM_COUNT=("16" "32" "64" "128" "256" "512")
declare -a POLICY=("FIFO" "NRU" "LRU" "Opt")

# Check if the provided problem size is correct
B="f"
for i in "${PRBLM_SIZES[@]}"
do 
    if [ "$1" = "$i" ] 
    then
        B="t"
    fi
done
if [ "$B" = "f" ]
then
    echo "ERROR: Incorrect problem size provided" 
    exit 1
fi

# Check if the provided page frame size is correct
B="f"
for i in "${PG_FRM_SIZES[@]}"
do 
    if [ "$2" = "$i" ] 
    then
        B="t"
    fi
done
if [ "$B" = "f" ]
then
    echo "ERROR: Incorrect page frame size provided" 
    exit 1
fi

# Check if the provided page frame count is correct
B="f"
for i in "${PG_FRM_COUNT[@]}"
do 
    if [ "$3" = "$i" ] 
    then
        B="t"
    fi
done
if [ "$B" = "f" ]
then
    echo "ERROR: Incorrect page frame count provided" 
    exit 1
fi

# Check if the provided policy is correct
B="f"
for i in "${POLICY[@]}"
do 
    if [ "$4" = "$i" ] 
    then
        B="t"
    fi
done
if [ "$B" = "f" ]
then
    echo "ERROR: Incorrect policy provided" 
    exit 1
fi

# Run the programs and print the output
echo $(eval "cd Programs
./nameSorter $1 listaccess | ./pageRefGen $2 | ./$4 $3")



