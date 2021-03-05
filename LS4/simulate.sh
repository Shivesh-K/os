C=0
IDX=0

# Loop through all the arguments
args=("$@")
for i in 1 2 3 4
do
    if [ "${args[$((i-1))]}" = "All" ]
    then
        # Increment everythime there is an 'All'
        ((C=C+1))
        # Store the index at which it appers
        IDX=$i
    fi
done

# If the number of 'All's is greater than 1, then exit
if [ $C -gt 1 ] 
then
    echo "ERROR: 'All' can be used atmost 1 time. Was used $C times."
    exit 1
fi

# If there is no 'All', execute simulate101.sh with provided arguments
if [ $C -eq 0 ]
then 
    bash ./simulate101.sh "$1" "$2" "$3" "$4"
fi

# Declare all the possible values for arguments
declare -a PRBLM_SIZES=("2000" "3000" "4000" "5000" "6000" "7000" "8000")
declare -a PG_FRM_SIZES=("16" "32" "64" "128" "256")
declare -a PG_FRM_COUNTS=("16" "32" "64" "128" "256" "512")
declare -a POLICIES=("FIFO" "NRU" "LRU" "Opt")

# Switch case of the index where 'All' occured 
case "$IDX" in
    "1") 
        for i in "${PRBLM_SIZES[@]}"
        do
            bash ./simulate101.sh "$i" "$2" "$3" "$4"
        done
    ;;
    "2") 
        for i in "${PG_FRM_SIZES[@]}"
        do
            bash ./simulate101.sh "$1" "$i" "$3" "$4"
        done
    ;;
    "3") 
        for i in "${PG_FRM_COUNTS[@]}"
        do
            bash ./simulate101.sh "$1" "$2" "$i" "$4"
        done
    ;;
    "4") 
        for i in "${POLICIES[@]}"
        do
            bash ./simulate101.sh "$1" "$2" "$3" "$i"
        done
    ;;
esac

