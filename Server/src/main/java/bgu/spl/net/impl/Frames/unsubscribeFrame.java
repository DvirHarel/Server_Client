package bgu.spl.net.impl.Frames;

import java.util.ArrayList;
import java.util.Arrays;

public class unsubscribeFrame extends Frame implements clientFrame{
    private String id;

    public unsubscribeFrame(String completeMsg) {
        super("RECEIPT");
        ArrayList<String> tmp = new ArrayList<>();
        tmp.addAll(Arrays.asList(completeMsg.split("\n")));
        id = getAfterChar(tmp.get(3), ':');
    }

    public String getId() {
        return id;
    }

    @Override
    public String toString() {
        return getContent() + "\n" + "receipt-id:" + getId() + "\n";
    }

    @Override
    public boolean isLegal(String s) {
        ArrayList<String> tmp = toArrayList(s);
        if (!tmp.get(1).startsWith("id:")) return false;
        return tmp.get(2).equals("");
    }
}
