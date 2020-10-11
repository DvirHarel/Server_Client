package bgu.spl.net.srv;
import bgu.spl.net.impl.Frames.*;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Pair;

public class StompBookClubImpl<T> implements StompMessagingProtocol<String> {
    private int connectionID;
    private ConnectionsImpl<String> connections;
    private boolean isTerminated;
   // private HashMap<String,List<Users.User>> topics = new HashMap<>();


    public StompBookClubImpl() {
    }

    public int getConnectionId(){return connectionID;}

    public void start(int connectionId, ConnectionsImpl<String> connections) {
        this.connectionID = connectionId;
        this.connections = connections;
    }

    @Override
    public boolean shouldTerminate() {
        return isTerminated;
    }

    @Override
    public void process(String msg) {
        String type = msg.substring(0,msg.indexOf('\n'));
        String result;
        switch (type) {
            case "CONNECT":
                result = process(new connectFrame(msg));
                connections.send(this.connectionID, result);
                break;
            case "DISCONNECT":
                isTerminated = true;
                result = process(new disconnectFrame(msg));
                connections.send(this.connectionID, result);
                connections.disconnect(this.connectionID);
                break;
            case "SEND":
                process(new sendFrame(msg));
                break;
            case "SUBSCRIBE":
                process(new subscribeFrame(msg));
                break;
            case "UNSUBSCRIBE":
                process(new unsubscribeFrame(msg));
                break;
            default:
                //Error
                //TODO
        }
    }

    private String process(connectFrame connect) {
        String s = ((connections).tryConnect(connect.getAcceptVersion(), connect.getLogin(), connect.getPasscode(), this.connectionID));
        if (s.equals("CONNECTED")) {
            connectedFrame connected = new connectedFrame(connect.getAcceptVersion());
            System.out.println(connected.toString());
            return connected.toString();
        } else {
            errorFrame error = new errorFrame("Connect has no receipt id", s, connect, "s");
            return error.toString();
        }
    }

    private String process(disconnectFrame disconnect) {
        receiptFrame receipt = new receiptFrame(disconnect.getReceipt());
        System.out.println(receipt.toString());
        return (receipt.toString());
    }

    private void process(sendFrame send) {
            for (Pair<String, String> pair : (connections).getConnectionSubId().keySet()) {
                if (pair.getSecond().equals(send.getDest())) {
                    for (Pair<String, Integer> connectionIds : (connections).getUserConnectionId()) {
                        if (connectionIds.getFirst().equals(pair.getFirst())) {
                            messageFrame m = new messageFrame((connections).getConnectionSubId().get(pair), String.valueOf((connections).getAndIncMsgCounter()), send.getDest(), send.getMsg());
                            connections.send(connectionIds.getSecond(), m.toString());
                            break;
                        }
                    }
                }
            }
    }
    /*
    CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system

all: EchoClient
	g++ -o bin/echoExample bin/connectionHandler.o bin/echoClient.o $(LDFLAGS)

EchoClient: bin/connectionHandler.o bin/echoClient.o

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/echoClient.o: src/echoClient.cpp
	g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp

.PHONY: clean
clean:
	rm -f bin/*
    */

    private void process(subscribeFrame subscribe) {
        (connections).subscribe(subscribe.getDest(), subscribe.getId(), this.connectionID);
        receiptFrame receipt = new receiptFrame(subscribe.getReceipt());
        System.out.println(receipt.toString());
        connections.send(this.connectionID,(receipt.toString()));
    }

    private void process(unsubscribeFrame unsubscribe) {
        (connections).unsubscribe(unsubscribe.getId(), this.connectionID);
        System.out.println(unsubscribe.toString());
        connections.send(this.connectionID,(unsubscribe.toString()));
    }
}
