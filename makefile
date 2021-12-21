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


#BIN_FLDR := $(shell mkdir -p bin)
#BUILD_FLDR := $(shell mkdir -p build)


main.o: main.c $(PT_HDR)validation.h $(PT_HDR)user.h $(PT_HDR)task.h $(PT_HDR)debug.h $(PT_HDR)database.h $(PT_HDR)appointment.h
	$(CC) -c main.c -o build/main.o

appointment.o: $(PT_SRC)appointment.c $(PT_HDR)validation.h $(PT_HDR)user.h $(PT_HDR)receipt.h $(PT_HDR)appointment.h
	$(CC) -c $(IN_LIB1) src/appointment.c -o build/appointment.o

database.o: $(PT_SRC)database.c $(PT_HDR)validation.h $(PT_HDR)appointment.h
	$(CC) -c $(IN_LIB2) src/database.c -o build/database.o

receipt.o: $(PT_SRC)receipt.c $(PT_HDR)validation.h $(PT_HDR)appointment.h $(PT_HDR)receipt.h 
	$(CC) -c $(IN_LIB3) src/receipt.c -o build/receipt.o

task.o:  $(PT_SRC)task.c $(PT_HDR)validation.h $(PT_HDR)task.h 
	$(CC) -c $(IN_LIB4) src/task.c -o build/task.o

validation.o:  $(PT_SRC)validation.c $(PT_HDR)validation.h $(PT_HDR)appointment.h 
	$(CC) -c $(IN_LIB5) src/validation.c -o build/validation.o

user.o: $(PT_SRC)user.c $(PT_HDR)validation.h $(PT_HDR)appointment.h $(PT_HDR)user.h 
	$(CC) -c $(IN_LIB6) src/user.c -o build/user.o
	
app: main.o appointment.o database.o receipt.o task.o user.o validation.o
	$(CC) -g -o bin/app.exe build/main.o build/appointment.o build/database.o build/receipt.o build/task.o build/user.o build/validation.o 

clean: 
	del /Q build