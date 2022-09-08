CC = g++

CCFLAGS = -c -g -Wall
LDFLAGS = -o
IFLAGS = -I

OBJ = obj
SRC = src
BIN = bin
INC = inc


all:server client 

server:$(OBJ)/udpclient.o $(OBJ)/udpserver.o $(OBJ)/tcpclient.o $(OBJ)/tcpserver.o $(OBJ)/functions.o $(OBJ)/serverfuncmain.o
	$(CC) $(LDFLAGS) $(BIN)/server $(OBJ)/udpclient.o $(OBJ)/udpserver.o $(OBJ)/tcpclient.o $(OBJ)/tcpserver.o $(OBJ)/functions.o $(OBJ)/serverfuncmain.o -lpthread
$(OBJ)/tcpserver.o: $(SRC)/tcpserver.cpp
	$(CC) $(CCFLAGS) $(SRC)/tcpserver.cpp $(IFLAGS) $(INC)
	mv *.o $(OBJ)/
$(OBJ)/functions.o: $(SRC)/functions.cpp
	$(CC) $(CCFLAGS) $(SRC)/functions.cpp $(IFLAGS) $(INC)
	mv *.o $(OBJ)/
$(OBJ)/serverfuncmain.o:$(SRC)/serverfuncmain.cpp
	$(CC) $(CCFLAGS) $(SRC)/serverfuncmain.cpp $(IFLAGS) $(INC)
	mv *.o $(OBJ)/


client: $(OBJ)/udpclient.o $(OBJ)/udpserver.o $(OBJ)/tcpclient.o $(OBJ)/tcpserver.o $(OBJ)/functions.o $(OBJ)/clientfuncmain.o
	$(CC) $(LDFLAGS) $(BIN)/client $(OBJ)/udpclient.o $(OBJ)/udpserver.o $(OBJ)/tcpclient.o $(OBJ)/tcpserver.o $(OBJ)/functions.o $(OBJ)/clientfuncmain.o -lpthread

$(OBJ)/udpclient.o: $(SRC)/udpclient.cpp
	$(CC) $(CCFLAGS) $(SRC)/udpclient.cpp $(IFLAGS) $(INC)
	mv *.o $(OBJ)/
$(OBJ)/udpserver.o: $(SRC)/udpserver.cpp
	$(CC) $(CCFLAGS) $(SRC)/udpserver.cpp $(IFLAGS) $(INC)
	mv *.o $(OBJ)/
$(OBJ)/tcpclient.o: $(SRC)/tcpclient.cpp
	$(CC) $(CCFLAGS) $(SRC)/tcpclient.cpp $(IFLAGS) $(INC)
	mv *.o $(OBJ)/
$(OBJ)/clientfuncmain.o:$(SRC)/clientfuncmain.cpp
	$(CC) $(CCFLAGS) $(SRC)/clientfuncmain.cpp $(IFLAGS) $(INC)
	mv *.o $(OBJ)/
valgrind: $(BIN)/client $(BIN)/server
	valgrind --leak-check=full --show-reachable=yes $(BIN)/client 1>$(BIN)/valgrindclient.txt $(BIN)/server 1>$(BIN)/valgringserver.txt


clean:
	rm $(OBJ)/*.o
	rm $(BIN)/server $(BIN)/client
	@echo "Cleaning Done"
