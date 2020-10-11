CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system
THREADFLAGS:=-pthread

default: StompBookClubClient
	g++ -o bin/StompBookClubClient bin/connectFrame.o bin/connectionHandler.o bin/disconnectFrame.o bin/keyBoard.o bin/Protocol.o bin/sendFrame.o bin/StompBookClubClient.o bin/subscribeFrame.o bin/unsubscribeFrame.o bin/User.o $(LDFLAGS) $(THREADFLAGS)

StompBookClubClient: bin/User.o bin/connectFrame.o bin/connectionHandler.o bin/disconnectFrame.o bin/keyBoard.o bin/Protocol.o bin/sendFrame.o bin/StompBookClubClient.o bin/subscribeFrame.o bin/unsubscribeFrame.o

bin/connectFrame.o: src/connectFrame.cpp
	g++ $(CFLAGS) -o bin/connectFrame.o src/connectFrame.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/disconnectFrame.o: src/disconnectFrame.cpp
	g++ $(CFLAGS) -o bin/disconnectFrame.o src/disconnectFrame.cpp

bin/keyBoard.o: src/keyBoard.cpp
	g++ $(CFLAGS) -o bin/keyBoard.o src/keyBoard.cpp

bin/Protocol.o: src/Protocol.cpp
	g++ $(CFLAGS) -o bin/Protocol.o src/Protocol.cpp

bin/sendFrame.o: src/sendFrame.cpp
	g++ $(CFLAGS) -o bin/sendFrame.o src/sendFrame.cpp

bin/StompBookClubClient.o: src/StompBookClubClient.cpp
	g++ $(CFLAGS) -o bin/StompBookClubClient.o src/StompBookClubClient.cpp

bin/subscribeFrame.o: src/subscribeFrame.cpp
	g++ $(CFLAGS) -o bin/subscribeFrame.o src/subscribeFrame.cpp

bin/unsubscribeFrame.o: src/unsubscribeFrame.cpp
	g++ $(CFLAGS) -o bin/unsubscribeFrame.o src/unsubscribeFrame.cpp

bin/User.o: src/User.cpp
	g++ $(CFLAGS) -o bin/User.o src/User.cpp

.PHONY: clean
clean:
	rm -f bin/*
