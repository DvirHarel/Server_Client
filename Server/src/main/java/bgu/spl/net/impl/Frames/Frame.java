package bgu.spl.net.impl.Frames;

import java.util.ArrayList;
import java.util.Arrays;

public abstract class Frame {
    private String content;

    public String getContent() {
        return content;
    }


    public Frame (String content){
        this.content = content;
    }

    public String getAfterChar(String s, char c) {
        int loc = s.indexOf(c);
        return s.substring(loc+1);
    }

    @Override
    public abstract String toString();

    public ArrayList<String> toArrayList(String s) {
        return new ArrayList<>(Arrays.asList(s.split("\n")));
    }
}
