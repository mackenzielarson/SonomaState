H3.out : larsonH3.o fraction.o SetLimits.o
	g++ -std=c++11 -O3 -o H3.out larsonH3.o fraction.o SetLimits.o

T3.out : larsonT3.o fraction.o SetLimits.o
	g++ -std=c++11 -O3 -o T3.out larsonT3.o fraction.o SetLimits.o

larsonH3.o : larsonH3.cpp SetLimits.h fraction.h
	g++ -std=c++11 -O3 -c larsonH3.cpp -g

larsonT3.o : larsonT3.cpp SetLimits.h fraction.h
	g++ -std=c++11 -O3 -c larsonT3.cpp -g

fraction.o : fraction.cpp fraction.h
	g++ -std=c++11 -O3 -c fraction.cpp -g

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -std=c++11 -O3 -c SetLimits.cpp -g

run : H3.out H3.input T3.out T3.input 
	./H3.out H3.input
	./T3.out T3.input 

clean :
	rm -f *.o H3*.out

submit : larsonH3.cpp larsonT3.cpp fraction.h fraction.cpp makefile README.txt
	rm -rf larsonH3
	mkdir larsonH3
	cp larsonH3.cpp larsonH3
	cp larsonT3.cpp larsonH3
	cp fraction.h larsonH3
	cp fraction.cpp larsonH3
	cp makefile larsonH3
	cp README.txt larsonH3
	tar cfvz larsonH3.tgz larsonH3
	cp larsonH3.tgz ~tiawatts/cs460drop
