H4.out: larsonH4.o fraction.o SetLimits.o vector.o
	gcc -g -O3 -o H4.out larsonH4.c fraction.o SetLimits.o vector.o

larsonH4.o : larsonH4.c fraction.h vector.h
	gcc -g -O3 -c larsonH4.c

SetLimits.o : SetLimits.c SetLimits.h
	gcc -g -O3 -c SetLimits.c

vector.o: vector.c vector.h
	gcc -g -O3 -c vector.c

fraction.o : fraction.c fraction.h
	gcc -g -O3 -c fraction.c

clean:
	rm *.o H4.out

run:
	./H4.out wattstest.txt

submit : larsonH4.c fraction.h fraction.c makefile
	rm -rf larsonH4
	mkdir larsonH4
	cp larsonH4.c larsonH4
	cp fraction.h larsonH4
	cp fraction.c larsonH4
	cp vector.c larsonH4
	cp vector.h larsonH4
	cp SetLimits.c larsonH4
	cp SetLimits.h larsonH4
	cp makefile larsonH4
	tar cfvz larsonH4.tgz larsonH4
	cp larsonH4.tgz ~tiawatts/cs460drop
