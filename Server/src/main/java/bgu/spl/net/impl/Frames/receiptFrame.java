package bgu.spl.net.impl.Frames;

public class receiptFrame extends Frame {
    private String receiptID;

    public receiptFrame(String receiptID) {
        super("RECEIPT");
        this.receiptID = receiptID;
    }

    public String getReceiptID() {
        return receiptID;
    }

    @Override
    public String toString() {
        return getContent() + "\n" + "receipt-id:" + getReceiptID() + "\n";
    }
}
