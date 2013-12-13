CPP=src/*.cpp
HPP=src/*.h src/tree/*.h src/hash/*.h

.SUFFIXES:
	

obj/test: ${CPP} ${HPP}
	g++ -Wall -std=c++11 -DDEBUG -O2 ${CPP} -o obj/test

${CPP}:
	
clean:
	rm -f obj/test
