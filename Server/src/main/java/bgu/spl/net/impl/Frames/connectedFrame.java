package bgu.spl.net.impl.Frames;

public class connectedFrame extends Frame {
    private String version;

    public String getVersion() {
        return version;
    }

    public connectedFrame(String version) {
        super("CONNECTED");
        this.version = version;
    }

    @Override
    public String toString() {
        return getContent() + "\n" + "version:" + getVersion() + "\n\n^@";
    }
}