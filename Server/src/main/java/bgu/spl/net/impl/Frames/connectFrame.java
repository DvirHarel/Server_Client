package bgu.spl.net.impl.Frames;

import java.util.ArrayList;
import java.util.Arrays;

public class connectFrame extends Frame implements clientFrame {

    private String acceptVersion;
    private String host;
    private String login;
    private String passcode;

    public connectFrame(String completeMsg) {
        super("CONNECT");
        ArrayList<String> tmp = new ArrayList<>();
        tmp.addAll(Arrays.asList(completeMsg.split("\n")));
        acceptVersion = getAfterChar(tmp.get(1), ':');
        host = getAfterChar(tmp.get(2), ':');
        login = getAfterChar(tmp.get(3), ':');
        passcode = getAfterChar(tmp.get(4), ':');
    }

    public String getAcceptVersion() {
        return acceptVersion;
    }

    public String getHost() {
        return host;
    }

    public String getLogin() {
        return login;
    }

    public String getPasscode() {
        return passcode;
    }

    @Override
    public String toString() {
        return getContent() + "ED" + "\n" + "accept-version:" + getAcceptVersion() + "\n\n^@"/*+ "\nhost:" + getHost() + "\nlogin:" + getLogin() + "\npasscode:" + getPasscode() + "\n"*/;
    }

    @Override
    public boolean isLegal(String s) {
        ArrayList<String> tmp = toArrayList(s);
        if (!tmp.get(1).startsWith("accept-version:")) return false;
        if (!tmp.get(2).startsWith("host:")) return false;
        if (!tmp.get(3).startsWith("login:")) return false;
        if (!tmp.get(4).startsWith("passcode:")) return false;
        return tmp.get(5).equals("");
    }
}
