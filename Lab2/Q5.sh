cd T2

for i in {0..5} ; do
	fname="test0$i" 
	cd $fname
	
	cd 01
	rm *.txt
	
	cd ..
	cd 02
	rm *.txt
	
	cd ../..
done	
