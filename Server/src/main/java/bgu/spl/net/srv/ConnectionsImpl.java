package bgu.spl.net.srv;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.Pair;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ConnectionsImpl<T> implements Connections<T> {
    private Map<Pair<String, String>, String> connectionSubId = new HashMap<>();//userName and genre RegistrationID
    private Map<String, String> userCredentials = new HashMap<>();//userName and password
    private List<String> loggedUsers = new ArrayList<>();//userName logged in
    private List<Pair<String, Integer>> userConnectionId = new ArrayList<>();//userName and ID
    private Map<Integer, ConnectionHandler<T>> connectionHandlerId = new HashMap<>();//ID and connectionHandler
    private int msgSent = 0;
    private static ConnectionsImpl connections;

    private ConnectionsImpl(){
    }

    public static ConnectionsImpl getInstance() {
        if ( connections == null)
            connections = new ConnectionsImpl();
        return connections;
    }
    public List<Pair<String, Integer>> getUserConnectionId() {
        return userConnectionId;
    }

    //@Override

    public synchronized int getAndIncMsgCounter() {
        this.msgSent++;
        return msgSent - 1;
    }

    @Override
    public boolean send(int connectionId, T msg) {
        ConnectionHandler<T> connectionHandler = connectionHandlerId.get(connectionId);
        //synchronized (connectionHandler) {
            if (!connectionHandlerId.containsKey(connectionId)) return false;
            else {
                connectionHandlerId.get(connectionId).send(msg);
            }
            return true;
        //}
    }

    @Override
    public void send(String channel, T msg) { //we shouldn't use this function because it doesn't insert the subscription id into the msg
        for (Pair<String, String> pair : getConnectionSubId().keySet()) {
            if (pair.getSecond().equals(channel)) {
                for (Pair<String, Integer> connectionIds : getUserConnectionId()) {
                    if (connectionIds.getFirst().equals(pair.getFirst())) {
                        synchronized (connectionHandlerId.get(connectionIds.getSecond())) {
                            send(connectionIds.getSecond(), msg);
                        }
                        break;
                    }
                }
            }
        }
    }

    @Override
    public void disconnect(int connectionId) {
        String user = "";
        for (Pair<String, Integer> userConnectionIds : userConnectionId) {
            if (userConnectionIds.getSecond() == connectionId) {
                user = userConnectionIds.getFirst();
                break;
            }
        }
        loggedUsers.remove(user);
        ConnectionHandler<T> connectionHandler = connectionHandlerId.get(connectionId);
        try {
            connectionHandler.close();
            connectionHandlerId.remove(connectionId);
        } catch (Exception ignore) {
        } //TODO
    }

    // @Override
    public Map<Pair<String, String>, String> getConnectionSubId() {
        return connectionSubId;
    }

    // @Override
    public String tryConnect(String acceptVersion, String username, String passcode, int connectionId) {
        String serverVersion = "1.2";
        if (!serverVersion.equals(acceptVersion)) return "Wrong accept-version";
        for (String user : userCredentials.keySet()) {
            if (user.equals(username)) {
                if (userCredentials.get(user).equals(passcode)) {
                    if (loggedUsers.contains(username)) {
                        return "User already logged in";
                    } else {
                        loggedUsers.add(username);
                        userConnectionId.add(new Pair<>(username, connectionId));
                        return "CONNECTED";
                    }
                } else {
                    return "Wrong password";
                }
            }
        }
        userCredentials.put(username, passcode);
        loggedUsers.add(username);
        userConnectionId.add(new Pair<>(username, connectionId));
        return "CONNECTED";
    }

    public void updateHandler(int connectionId, ConnectionHandler<T> handler){
        if (connectionHandlerId.get(connectionId) != null) System.out.println("WARNING: trying to push an existing connection (ConnectionsImp)");
        else connectionHandlerId.put(connectionId, handler);

    }

    // @Override
    public void subscribe(String dest, String id, int connectionId) {
        for (Pair<String, Integer> userConnection : userConnectionId) {
            if (userConnection.getSecond() == connectionId) {
                connectionSubId.put(new Pair<>(userConnection.getFirst(), dest), id);
                break;
            }
        }
    }

    //  @Override
    public void unsubscribe(String id, int connectionId) {
        Pair<String, String> remove = null;
        for (Pair<String, String> findToRemove : connectionSubId.keySet()) {
            if (connectionSubId.get(findToRemove).equals(id)) {
                remove = findToRemove;
                break;
            }
        }
        connectionSubId.remove(remove);
    }

    //@Override
    public Map<Integer, ConnectionHandler<T>> getConnectionHandlerId() {
        return connectionHandlerId;
    }

    @Override
    public ConnectionHandler<T> getConnectionHandler(int connectionId) {
        return connectionHandlerId.get(connectionId);
    }
}
