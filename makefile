all: main
#all: $(CHAR) recv.o sender.o

main: main.o
	g++ -g -o main main.o

main.o: main.cpp
	g++ -c -g main.cpp

tar:
	tar cvf p2-cphongsa.tar *.cpp *.h makefile *.pdf *.png

clean:
	rm *.o main outputfile	

# target: dependencies
# 	action
# ^ this is the template for the above code