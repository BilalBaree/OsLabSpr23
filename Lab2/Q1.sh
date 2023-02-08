s=$1

if [[ $2 -le $s ]]; 
then
s=$2
fi

if [[ $3 -le $s ]];
then
s=$3
fi

echo "Minimum Number : $s"
