# compiler used
CC = g++ 

# optional compile time flags (-O2, -O3 etc)
CFLAGS = -O3

EXE = showSTL.x

## Build targets

# root target (builds the final executable)

$(EXE):	main.o \
	getGeometryInput.o \
	readBINARY.o \
	readASCII.o
	$(CC) main.o getGeometryInput.o readBINARY.o readASCII.o -o $(EXE) -framework OpenGL -framework Cocoa -framework IOKit -L /usr/local/lib -lglfw

# compile dependencies

main.o: main.h main.cpp
	$(CC) $(CFLAGS) -I /usr/local/include -c main.cpp -o main.o

getGeometryInput.o: getGeometryInput.h getGeometryInput.cpp
	$(CC) $(CFLAGS) -c getGeometryInput.cpp -o getGeometryInput.o

readBINARY.o: readBINARY.h readBINARY.cpp
	$(CC) $(CFLAGS) -c readBINARY.cpp -o readBINARY.o

readASCII.o: readASCII.h readASCII.cpp
	$(CC) $(CFLAGS) -c readASCII.cpp -o readASCII.o

clean:
	/bin/rm -f *.o

veryclean:
	/bin/rm -f *.o *.x
