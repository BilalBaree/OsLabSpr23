cd T2

for i in {0..5} ; do
	fname="test0$i"
	cd $fname
	
	cd 01
	cat test.txt >> ../../merged.txt
	
	cd ..
	cd 02
	cat test.txt >> ../../merged.txt
	
	cd ../..
	
done
	
	
