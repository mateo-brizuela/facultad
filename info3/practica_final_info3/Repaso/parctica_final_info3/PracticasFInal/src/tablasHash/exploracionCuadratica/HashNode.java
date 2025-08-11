package tablasHash.exploracionCuadratica;

public class HashNode {
    private String key;
    private int value;

    // cosntructor
    public HashNode(String key, int value){
        this.key = key;
        this.value = value;
    }

    // getters y setters

    public void setKey(String key){
        this.key = key;
    }

    public String getKey(){
        return key;
    }

    public void setValue(int value){
        this.value = value;
    }

    public int getValue(){
        return value;
    }

}
