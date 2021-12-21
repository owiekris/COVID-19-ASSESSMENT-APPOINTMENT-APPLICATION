#PATH VARIABLES
CC = gcc
IN_SRC = -I ../src/
IN_HDR = -I ../include/
PT_SRC = ./src/
PT_HDR = ./include/
IN_LIB1=-I ../my_library_1/
IN_LIB2=-I ../my_library_2/
IN_LIB3=-I ../my_library_3/
IN_LIB4=-I ../my_library_4/
IN_LIB5=-I ../my_library_5/
IN_LIB6=-I ../my_library_6/
IN_LIB7=-I ../my_library_7/

main.o: main.c $(PT_HDR)tvalidation.h $(PT_HDR)tuser.h $(PT_HDR)ttask.h $(PT_HDR)tdebug.h $(PT_HDR)tdatabase.h $(PT_HDR)tappointment.h
	$(CC) -c main.c -o build/main.o

tappointment.o: $(PT_SRC)tappointment.c $(PT_HDR)tvalidation.h $(PT_HDR)tuser.h $(PT_HDR)treceipt.h $(PT_HDR)tappointment.h
	$(CC) -c $(IN_LIB1) src/tappointment.c -o build/tappointment.o

tdatabase.o: $(PT_SRC)tdatabase.c $(PT_HDR)tvalidation.h $(PT_HDR)tappointment.h
	$(CC) -c $(IN_LIB2) src/tdatabase.c -o build/tdatabase.o

treceipt.o: $(PT_SRC)treceipt.c $(PT_HDR)tvalidation.h $(PT_HDR)tappointment.h $(PT_HDR)treceipt.h 
	$(CC) -c $(IN_LIB3) src/treceipt.c -o build/treceipt.o

ttask.o:  $(PT_SRC)ttask.c $(PT_HDR)tvalidation.h $(PT_HDR)ttask.h 
	$(CC) -c $(IN_LIB4) src/ttask.c -o build/ttask.o

tvalidation.o:  $(PT_SRC)tvalidation.c $(PT_HDR)tvalidation.h $(PT_HDR)tappointment.h 
	$(CC) -c $(IN_LIB5) src/tvalidation.c -o build/tvalidation.o

tuser.o: $(PT_SRC)tuser.c $(PT_HDR)tvalidation.h $(PT_HDR)tappointment.h $(PT_HDR)tuser.h 
	$(CC) -c $(IN_LIB6) src/tuser.c -o build/tuser.o
	
test: main.o tappointment.o tdatabase.o treceipt.o ttask.o tuser.o tvalidation.o
	$(CC) -g -o bin/test.exe build/main.o build/tappointment.o build/tdatabase.o build/treceipt.o build/ttask.o build/tuser.o build/tvalidation.o 

clean: 
	del /Q build