package RTL;
import javax.swing.*;
import java.util.HashMap;

public class ObjValue {
    public String __toString() {
        throw new FatalError("Uncaught Error: Object of class a could not be converted to string");
    }

    public HashMap<String, Value> __getValues() {
        return new HashMap<>();
    }
}
