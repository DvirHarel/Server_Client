package bgu.spl.net.srv;

public class Pair<V,U> {
    private V first;
    private U second;


    public Pair(V first, U second){
        this.first=first;
        this.second=second;
    }
    public V getFirst(){
        return this.first;
    }
    public U getSecond(){
        return this.second;
    }
}
