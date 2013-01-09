
objects = InputParser.o InputParser_C.o 
     
InputParser : $(objects)
	ar rcs libInputParser.a InputParser.o
	ar rcs libInputParser_C.a InputParser_C.o 
InputParser_C.o  : InputParser_C.c InputParser_C.h
	cc -c InputParser_C.c

InputParser.o : InputParser.cpp InputParser.h
	cc -c InputParser.cpp

clean :
	rm libInputParser.a libInputParser_C.a $(objects)
