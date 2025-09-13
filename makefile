build:
	g++ Array.cpp driver.cpp -o Array

run: Array
	./Array

clean:
	rm *.gch *.out Array