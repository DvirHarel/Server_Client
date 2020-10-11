package bgu.spl.net.impl.Frames;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class messageFrame extends Frame {
    private String subscription;
    private String messageID;
    private String dest;
    private String message;

    public messageFrame(String subscription, String messageID, String dest, String message) {
        super("MESSAGE");
        this.subscription = subscription;
        this.messageID = messageID;
        this.dest = dest;
        this.message = message;
    }

    public String getSubscription() {
        return subscription;
    }

    public String getMessageID() {
        return messageID;
    }

    public String getDest() {
        return dest;
    }

    public String getMessage() {
        return message;
    }

    @Override
    public String toString() {
        return getContent()+ "\n" + "subscription:" + getSubscription() + "\n" + "Message-id:" + getMessageID() + "\ndestination:" + getDest() + "\n\n" + getMessage();
    }
}
