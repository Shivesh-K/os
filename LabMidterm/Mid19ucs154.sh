if ! ([ "$1" = "3000" ] || [ "$1" = "5000" ])
then
    exit 1
fi

FirstName=""
LastName=""
echo $0
d1=$(expr substr $0 12 1)
d2=$(expr substr $0 13 1)

if ([ `expr $d1 % 2` -eq 1 ] && [ `expr $d2 % 2` -eq 1 ])
then
    FirstName="Arnab"
    SecondName="Sharma"
elif ([ `expr $d1 % 2` -eq 0 ] && [ `expr $d2 % 2` -eq 1 ])
then
    FirstName="Peter"
    LastName="Modi"
elif ([ `expr $d1 % 2` -eq 1 ] && [ `expr $d2 % 2` -eq 0 ])
then
    FirstName="Rajiv"
    LastName="Kohli"
else
    FirstName="Zeenat"
    LastName="Biden"
fi

echo $LastName, $FirstName

gcc -o nameSorter nameSorter.c
./nameSorter $1 listnames >names$1.txt