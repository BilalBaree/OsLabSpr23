	mkdir T2
	cd T2

for i in {1..5} ; do
	fname="test0$i"
	mkdir $fname
	cd $fname
	
	mkdir 01
	cd 01
	
	touch test.txt
	date > test.txt
	cd ..
	
	mkdir 02
	cd 02
	touch test.txt
	date > test.txt
	cd ../..
done	
