package bgu.spl.net.impl.Frames;

import java.util.ArrayList;
import java.util.Arrays;

public class disconnectFrame extends Frame implements clientFrame{
    private String receipt;

    public disconnectFrame(String completeMsg) {
        super("DISCONNECT");
        ArrayList<String> tempStringArray = new ArrayList<>();
        tempStringArray.addAll(Arrays.asList(completeMsg.split("\n")));
        receipt = getAfterChar(tempStringArray.get(1), ':');
    }

    public String getReceipt() {
        return receipt;
    }

    @Override
    public String toString() {
        return getContent() + "\n" + "receipt:" + getReceipt() + "\n";
    }

    @Override
    public boolean isLegal(String s) {
        ArrayList<String> tmp = toArrayList(s);
        if (!tmp.get(1).startsWith("receipt:")) return false;
        return tmp.get(2).equals("");
    }
}
