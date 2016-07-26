P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P1.out *.gch

submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf larsonP1
	mkdir larsonP1
	cp Project1.cpp larsonP1
	cp table.h larsonP1
	cp LexicalAnalyzer.h larsonP1
	cp LexicalAnalyzer.cpp larsonP1
	cp SyntacticalAnalyzer.h larsonP1
	cp SyntacticalAnalyzer.cpp larsonP1
	cp SetLimits.cpp larsonP1
	cp SetLimits.h larsonP1
	cp makefile larsonP1
	cp README.txt larsonP1
	tar cfvz larsonP1.tgz larsonP1
	cp larsonP1.tgz ~tiawatts/cs460drop
