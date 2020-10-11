package bgu.spl.net.impl.Frames;

import java.util.ArrayList;
import java.util.Arrays;

public class subscribeFrame extends Frame implements clientFrame{
    private String dest;
    private String id;
    private String receipt;

    public subscribeFrame(String completeMsg) {
        super("SUBSCRIBE");
        ArrayList<String> tmp = new ArrayList<>();
        tmp.addAll(Arrays.asList(completeMsg.split("\n")));
        dest = getAfterChar(tmp.get(1), ':');
        id = getAfterChar(tmp.get(2), ':');
        receipt = getAfterChar(tmp.get(3),':');
    }

    public String getDest() {
        return dest;
    }

    public String getId() {
        return id;
    }

    public String getReceipt() {
        return receipt;
    }

    @Override
    public String toString() {
        return getContent() + "\n" + "destination:" + getDest() + "\nid:" + getId() + "\n";
    }

    @Override
    public boolean isLegal(String s) {
        ArrayList<String> tmp = toArrayList(s);
        if (!tmp.get(1).startsWith("destination:")) return false;
        if (!tmp.get(2).startsWith("id:")) return false;
        return tmp.get(3).equals("");
    }
}
