CPPFLAGS= -c -g -Wall -pedantic -std=c++17 

__start__: graf
	./graf
obj:
	mkdir -p obj

graf: obj obj/main.o obj/Menu.o  obj/GraphMatrix.o obj/GraphList.o obj/GraphGenerator.o obj/KruskalVertice.o obj/Clock.o obj/Edge.o
	g++ -o graf obj/main.o obj/Menu.o  obj/GraphMatrix.o obj/GraphList.o obj/GraphGenerator.o obj/KruskalVertice.o obj/Clock.o obj/Edge.o -lpthread

obj/main.o: src/main.cpp inc/Menu.h
	g++ ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/Menu.o: inc/Menu.h inc/GraphGenerator.h inc/Clock.h inc/GraphMatrix.h inc/GraphList.h 
	g++ ${CPPFLAGS} -o obj/Menu.o src/Menu.cpp

obj/GraphGenerator.o: inc/GraphGenerator.h inc/Edge.h
	g++ ${CPPFLAGS} -o obj/GraphGenerator.o src/GraphGenerator.cpp

obj/KruskalVertice.o: inc/KruskalVertice.h
	g++ ${CPPFLAGS} -o obj/KruskalVertice.o src/KruskalVertice.cpp

obj/Clock.o: inc/Clock.h
	g++ ${CPPFLAGS} -o obj/Clock.o src/Clock.cpp

obj/Edge.o: inc/Edge.h
	g++ ${CPPFLAGS} -o obj/Edge.o src/Edge.cpp

obj/GraphList.o: inc/GraphList.h inc/Edge.h inc/KruskalVertice.h
	g++ ${CPPFLAGS} -o obj/GraphList.o src/GraphList.cpp

obj/GraphMatrix.o: inc/GraphMatrix.h inc/Edge.h inc/KruskalVertice.h
	g++ ${CPPFLAGS} -o obj/GraphMatrix.o src/GraphMatrix.cpp

clear:
	rm -rf obj/.o graf