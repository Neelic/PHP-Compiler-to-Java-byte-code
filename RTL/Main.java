package RTL;

import java.util.HashMap;

public class Main {
    public static void main(String[] args) {
        var tmp = new Value();

        for (int i = 0; i < 3; i++) {
            tmp = tmp.toArray();
            tmp.addToArray(new Value());
        }
    }
}
