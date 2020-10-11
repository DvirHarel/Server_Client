package bgu.spl.net.impl.Frames;

import java.util.ArrayList;
import java.util.Arrays;

public class sendFrame extends Frame implements clientFrame {
    private String dest;
    private String msg;

    public sendFrame(String completeMsg) {
        super("SEND");
        ArrayList<String> tmp = new ArrayList<>();
        tmp.addAll(Arrays.asList(completeMsg.split("\n")));
        dest = getAfterChar(tmp.get(1), ':');
        msg = tmp.get(3);
    }

    public String getDest() {
        return dest;
    }

    public String getMsg() {
        return msg;
    }

    @Override
    public String toString() {
        return getContent() + "\n" + "destination" + getDest() + "\n\n" + getMsg();
    }

    @Override
    public boolean isLegal(String s) {
        ArrayList<String> tmp = toArrayList(s);
        if (!tmp.get(1).startsWith("destination:")) return false;
        return tmp.get(2).equals("");
    }
}
