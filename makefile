build:
	g++ Array.h driver.cpp -o Array

run: Array
	./Array

clean:
	rm *.gch *.out Array