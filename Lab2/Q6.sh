echo "Enter Total No Of Fibonacci Numbers you want to print? : " ; read N
a=0
b=1

for ((i=0;i<N;i++)) ; do
	echo -n "$a "
	fn=$((a + b))
	a=$b
	b=$fn
done

