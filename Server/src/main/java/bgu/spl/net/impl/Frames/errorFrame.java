package bgu.spl.net.impl.Frames;

public class errorFrame extends Frame{
    private String message;
    private String receiptID;
    private Frame frame;
    private String messageDesc;

    public String getReceiptID() {
        return receiptID;
    }

    public String getMessage() {
        return message;
    }

    public Frame getFrame() {
        return this.frame;
    }

    public String getMessageDesc() {
        return messageDesc;
    }

    public errorFrame(String receiptID, String message, Frame frame, String messageDesc) {
        super("ERROR");
        this.message = message;
        this.receiptID = receiptID;
        this.frame = frame;
        this.messageDesc = messageDesc;
    }

    @Override
    public String toString() {
        return getContent() + "\n" + "receipt-id: " + getReceiptID() + "\nmessage: " + getMessage() + "\n\nThe message:\n-----\n" + frame.toString() + "\n-----\n" + getMessageDesc();
    }
}
