declare -a PRBLM_SIZES=("2000" "3000" "4000" "5000" "6000" "7000" "8000")
declare -a PG_FRM_SIZES=("16" "32" "64" "128" "256")
declare -a PG_FRM_COUNT=("16" "32" "64" "128" "256" "512")
declare -a POLICY=("FIFO" "NRU" "LRU" "Opt")

V1="f"
V2="f"
V3="f"
V4="f"

# Check if the provided problem size is correct
for i in "${PRBLM_SIZES[@]}"
do 
    if [ "$1" = "$i" ] 
    then
        V1="t"
    fi
done
if [ "$V1" = "f" ]
then
    echo "ERROR: Incorrect problem size provided" 
    exit 1
fi

# Check if the provided page frame size is correct
for i in "${PG_FRM_SIZES[@]}"
do 
    if [ "$2" = "$i" ] 
    then
        V2="t"
    fi
done
if [ "$V2" = "f" ]
then
    echo "ERROR: Incorrect page frame size provided" 
    exit 1
fi

# Check if the provided page frame count is correct
for i in "${PG_FRM_COUNT[@]}"
do 
    if [ "$3" = "$i" ] 
    then
        V3="t"
    fi
done
if [ "$V3" = "f" ]
then
    echo "ERROR: Incorrect page frame count provided" 
    exit 1
fi

# Check if the provided policy is correct
for i in "${POLICY[@]}"
do 
    if [ "$4" = "$i" ] 
    then
        V4="t"
    fi
done
if [ "$V4" = "f" ]
then
    echo "ERROR: Incorrect policy provided" 
    exit 1
fi

# Run the programs and print the output
echo $(eval "cd Programs
./nameSorter $1 listaccess | ./pageRefGen $2 | ./$4 $3")



