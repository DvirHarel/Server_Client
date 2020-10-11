package bgu.spl.net.impl.stomp;

import bgu.spl.net.srv.Server;
import bgu.spl.net.srv.StompBookClubImpl;
import bgu.spl.net.srv.StompMessageEncoderDecoder;

public class StompServer {

    public static void main(String[] args) throws Exception {
        if (args.length != 2) {
            throw new Exception("Number of arguments is invalid");
        }
        if (args[1].equals("tpc")) {
            Server.threadPerClient(Integer.parseInt(args[0]), //port
                    StompBookClubImpl::new,// , //protocol factory
                    StompMessageEncoderDecoder::new).serve(); //message encoder decoder factory
        } else if (args[1].equals("reactor")) {
            Server.reactor(Runtime.getRuntime().availableProcessors(),
                    Integer.parseInt(args[0]), //port
                    StompBookClubImpl::new,// , //protocol factory
                    StompMessageEncoderDecoder::new).serve();
        } else throw new Exception("Server type is invalid");
    }
}
