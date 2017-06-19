# compiler used
CC = g++-4.8 

# optional compile time flags (-O2, -O3 etc)
CFLAGS = -O3

EXE = showSTL.x

## Build targets

# root target (builds the final executable)

$(EXE):	main.o \
	getGeometryInput.o \
	readBINARY.o \
	readASCII.o \
	drawGeometry.o \
	createVertexArray.o
	$(CC) main.o getGeometryInput.o readBINARY.o readASCII.o drawGeometry.o createVertexArray.o -o $(EXE) -L /usr/local/lib -lglfw3 -lGL -lGLU -lGLEW -lX11 -lpthread -ldl -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor

# compile dependencies

main.o: main.h main.cpp
	$(CC) $(CFLAGS) -I /usr/local/include -c main.cpp -o main.o

getGeometryInput.o: getGeometryInput.h getGeometryInput.cpp
	$(CC) $(CFLAGS) -c getGeometryInput.cpp -o getGeometryInput.o

readBINARY.o: readBINARY.h readBINARY.cpp
	$(CC) $(CFLAGS) -c readBINARY.cpp -o readBINARY.o

readASCII.o: readASCII.h readASCII.cpp
	$(CC) $(CFLAGS) -c readASCII.cpp -o readASCII.o

drawGeometry.o: drawGeometry.h drawGeometry.cpp
	$(CC) $(CFLAGS) -I /usr/local/include -c drawGeometry.cpp -o drawGeometry.o

createVertexArray.o: createVertexArray.h createVertexArray.cpp
	$(CC) $(CFLAGS) -c createVertexArray.cpp -o createVertexArray.o

clean:
	/bin/rm -f *.o

veryclean:
	/bin/rm -f *.o *.x
