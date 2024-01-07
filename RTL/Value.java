import java.util.HashMap;

public class Value {
    protected TypeValue typeVal;
    private int intVal;
    private double floatVal;
    private String stringVal;
    private boolean boolVal;
    private HashMap<String, Value> arrayVal = null;
    private ObjValue objVal = null;
    private int lastArrayIndex = -1;

    public Value(int intVal) {
        typeVal = TypeValue.intVal;
        this.intVal = intVal;
    }

    public Value(double floatVal) {
        typeVal = TypeValue.floatVal;
        this.floatVal = floatVal;
    }

    public Value(String stringVal) {
        typeVal = TypeValue.stringVal;
        this.stringVal = stringVal;
    }

    public Value(boolean boolVal) {
        typeVal = TypeValue.boolVal;
        this.boolVal = boolVal;
    }

    public Value(HashMap<String, Value> arrayVal) {
        typeVal = TypeValue.arrayVal;
        this.arrayVal = arrayVal;
    }

    public Value(ObjValue objVal) {
        typeVal = TypeValue.objectVal;
        this.objVal = objVal;
    }

    public TypeValue getType() {
        return typeVal;
    }

    public int getInt() {
        if (typeVal == TypeValue.intVal) return intVal;
        else throw new RuntimeException("Not same type");
    }

    public double getFloat() {
        if (typeVal == TypeValue.floatVal) return floatVal;
        else throw new RuntimeException("Not same type");
    }

    public String getString() {
        if (typeVal == TypeValue.stringVal) return stringVal;
        else throw new RuntimeException("Not same type");
    }

    public boolean getBool() {
        if (typeVal == TypeValue.boolVal) return boolVal;
        else throw new RuntimeException("Not same type");
    }

    public HashMap<String, Value> getArrayVal() {
        if (typeVal == TypeValue.arrayVal) return arrayVal;
        else throw new RuntimeException("Not same type");
    }

    public ObjValue getObjVal() {
        if (typeVal == TypeValue.objectVal) return objVal;
        else throw new RuntimeException("Not same type");
    }

    public Value add(Value other) {
        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(intVal + other.getInt());
                    }
                    case floatVal -> {
                        return new Value(intVal + other.getFloat());
                    }
                }
            }
            case floatVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(floatVal + other.getInt());
                    }
                    case floatVal -> {
                        return new Value(floatVal + other.getFloat());
                    }
                }
            }
            case stringVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(stringVal + other.getInt());
                    }
                    case floatVal -> {
                        return new Value(stringVal + other.getFloat());
                    }
                    case stringVal -> {
                        return new Value(stringVal + other.getString());
                    }
                }
            }
            case boolVal -> {
                switch (other.getType()) {
                    case boolVal -> {
                        return new Value(boolVal | other.getBool());
                    }
                    case intVal -> {
                        return new Value((boolVal ? 1 : 0) + other.getInt());
                    }
                    case floatVal -> {
                        return new Value(other.getFloat() + (boolVal ? 1 : 0));
                    }
                }
            }
        }

        throw new RuntimeException(
                "Fatal error: Uncaught TypeError: Unsupported operand types: "
                        + this.typeToString()
                        + " + "
                        + other.typeToString()
        );
    }

    public Value sub(Value other) {
        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(intVal - other.getInt());
                    }
                    case floatVal -> {
                        return new Value(intVal - other.getFloat());
                    }
                }
            }
            case floatVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(floatVal - other.getInt());
                    }
                    case floatVal -> {
                        return new Value(floatVal - other.getFloat());
                    }
                }
            }
        }

        throw new RuntimeException(
                "Fatal error: Uncaught TypeError: Unsupported operand types: "
                        + this.typeToString()
                        + " - "
                        + other.typeToString()
        );
    }

    public Value mul(Value other) {
        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(intVal * other.getInt());
                    }
                    case floatVal -> {
                        return new Value(intVal * other.getFloat());
                    }
                }
            }
            case floatVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(floatVal * other.getInt());
                    }
                    case floatVal -> {
                        return new Value(floatVal * other.getFloat());
                    }
                }
            }
        }

        throw new RuntimeException(
                "Fatal error: Uncaught TypeError: Unsupported operand types: "
                        + this.typeToString()
                        + " * "
                        + other.typeToString()
        );
    }

    public Value div(Value other) {
        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(intVal / other.getInt());
                    }
                    case floatVal -> {
                        return new Value(intVal / other.getFloat());
                    }
                }
            }
            case floatVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(floatVal / other.getInt());
                    }
                    case floatVal -> {
                        return new Value(floatVal / other.getFloat());
                    }
                }
            }
        }

        throw new RuntimeException(
                "Fatal error: Uncaught TypeError: Unsupported operand types: "
                        + this.typeToString()
                        + " / "
                        + other.typeToString()
        );
    }

    public Value mod(Value other) {
        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(intVal % other.getInt());
                    }
                    case floatVal -> {
                        return new Value(intVal % other.getFloat());
                    }
                }
            }
            case floatVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(floatVal % other.getInt());
                    }
                    case floatVal -> {
                        return new Value(floatVal % other.getFloat());
                    }
                }
            }
        }

        throw new RuntimeException(
                "Fatal error: Uncaught TypeError: Unsupported operand types: "
                        + this.typeToString()
                        + " % "
                        + other.typeToString()
        );
    }

    public void addToArray(String index, Value other) {
        if (typeVal != TypeValue.arrayVal) {
            throw new RuntimeException("Fatal error: Uncaught Error: cannot use a scalar value as an array");
        }

        arrayVal.put(index, other);

        try {
            int ind = Integer.parseInt(index);

            if (ind > lastArrayIndex) lastArrayIndex = ind;
        } catch (NumberFormatException ignored) {
        }
    }

    public void addToArray(Value other) {
        if (typeVal == TypeValue.stringVal) {
            throw new RuntimeException("Fatal error: Uncaught Error: [] operator not supported for strings");
        }

        addToArray(String.valueOf(lastArrayIndex + 1), other);
    }

    public Value getArrayVal(String index) {
        if (typeVal != TypeValue.arrayVal && typeVal != TypeValue.stringVal) {
            String type = "";
            switch (typeVal) {
                case intVal -> type = "int";
                case boolVal -> type = "bool";
                case floatVal -> type = "float";
            }
            System.out.println("Warning: Trying to access array offset on value of type " + type);
        } else if (typeVal == TypeValue.stringVal) {
            int ind;

            try {
                ind = Integer.parseInt(index);
            } catch (NumberFormatException e) {
                System.out.println("Warning: String offset cast occurred");
                return null;
            }

            try {
                if (ind < 0) return new Value(String.valueOf(stringVal.charAt(stringVal.length() + ind)));
                else return new Value(String.valueOf(stringVal.charAt(ind)));
            } catch (IndexOutOfBoundsException e) {
                System.out.println("Warning: Uninitialized string offset " + ind);
                return null;
            }
        }

        if (index == null) index = "";

        if (!arrayVal.containsKey(index)) return null;

        return arrayVal.get(index);
    }

    public Value toIntVal() {
        return null;
    }

    public Value toFloatVal() {
        return null;
    }

    public Value toStringVal() {
        return null;
    }

    public Value toArray() {
        return null;
    }

    public Value toObject() {
        return null;
    }

    private String typeToString() {
        switch (typeVal) {
            case stringVal -> {
                return "string";
            }
            case intVal -> {
                return "int";
            }
            case floatVal -> {
                return "float";
            }
            case arrayVal -> {
                return "array";
            }
            case boolVal -> {
                return "bool";
            }
            case objectVal -> {
                return objVal.toString();
            }
            default -> throw new RuntimeException("Unknown type");
        }
    }
}
