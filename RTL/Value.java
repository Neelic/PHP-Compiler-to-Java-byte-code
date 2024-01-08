import java.util.HashMap;
import java.util.Map;

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
        if (other == null) return null;
        return addValue(other, false);
    }

    public Value add(int other) {
        return addValue(new Value(other), false);
    }

    public Value add(double other) {
        return addValue(new Value(other), false);
    }

    public Value concat(Value other) {
        if (other == null) return null;
        return addValue(other.toStringVal(), true);
    }

    public Value concat(String other) {
        if (other == null) return null;
        return addValue(new Value(other), false);
    }

    private Value addValue(Value other, boolean isConcat) {
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
                if (isConcat) {
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
            }
            case boolVal -> {
                switch (other.getType()) {
                    case boolVal -> {
                        return new Value((boolVal ? 1 : 0) + (other.getBool() ? 1 : 0));
                    }
                    case intVal -> {
                        return new Value((boolVal ? 1 : 0) + other.getInt());
                    }
                    case floatVal -> {
                        return new Value((boolVal ? 1 : 0) + other.getFloat());
                    }
                }
            }
        }

        System.out.println(
                "Fatal error: Uncaught TypeError: Unsupported operand types: "
                        + this.typeToString()
                        + " + "
                        + other.typeToString()
        );
        System.exit(1);
        return null;
    }

    public Value sub(Value other) {
        if (other == null) return null;

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

    public Value subFrom(int other) {
        return (new Value(other)).sub(this);
    }

    public Value subFrom(double other) {
        return (new Value(other)).sub(this);
    }

    public Value mul(Value other) {
        if (other == null) return null;

        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(intVal * other.getInt());
                    }
                    case floatVal -> {
                        return new Value(intVal * other.getFloat());
                    }
                    case boolVal -> {
                        return new Value(intVal * other.toIntVal().getInt());
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
                    case boolVal -> {
                        return new Value(floatVal * other.toFloatVal().getFloat());
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

    public Value mul(int other) {
        return mul(new Value(other));
    }

    public Value mul(double other) {
        return mul(new Value(other));
    }

    public Value div(Value other) {
        if (other == null) return null;

        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(intVal / other.getInt());
                    }
                    case floatVal -> {
                        return new Value(intVal / other.getFloat());
                    }
                    case boolVal -> {
                        return new Value(intVal / other.toIntVal().getInt());
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
                    case boolVal -> {
                        return new Value(floatVal / other.toFloatVal().getFloat());
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

    public Value div(int other) {
        return div(new Value(other));
    }

    public Value div(double other) {
        return div(new Value(other));
    }

    public Value mod(Value other) {
        if (other == null) return null;

        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        return new Value(intVal % other.getInt());
                    }
                    case floatVal -> {
                        return new Value(intVal % other.getFloat());
                    }
                    case boolVal -> {
                        return new Value(intVal % other.toIntVal().getInt());
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
                    case boolVal -> {
                        return new Value(floatVal % other.toFloatVal().getFloat());
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

    public Value mod(int other) {
        return mod(new Value(other));
    }

    public Value mod(double other) {
        return mod(new Value(other));
    }

    public void addToArray(String index, Value other) {
        if (other == null || index == null) return;

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

    public Value getArrayVal(int index) {
        return getArrayVal(String.valueOf(index));
    }

    public Value getArrayVal(Value index) {
        return getArrayVal(index.toStringVal().getString());
    }

    public Value toIntVal() {
        switch (typeVal) {
            case stringVal -> {
                StringBuilder result = new StringBuilder();
                for (int i = 0; i < stringVal.length(); i++) {
                    try {
                        String charNumber = String.valueOf(stringVal.charAt(i));
                        Integer.parseInt(charNumber);
                        result.append(charNumber);
                    } catch (NumberFormatException e) {
                        if (result.isEmpty()) return new Value(0);
                    }
                }

                return new Value(Integer.parseInt(result.toString()));
            }
            case intVal -> {
                return this;
            }
            case floatVal -> {
                return new Value((int) floatVal);
            }
            case arrayVal -> {
                return arrayVal.isEmpty() ? new Value(0) : new Value(1);
            }
            case boolVal -> {
                return new Value((boolVal ? 1 : 0));
            }
            case objectVal -> {
                return new Value(1);
            }
            default -> throw new RuntimeException("Unknown type");
        }
    }

    public Value toFloatVal() {
        switch (typeVal) {
            case stringVal -> {
                StringBuilder result = new StringBuilder();
                boolean hasDot = false;
                for (int i = 0; i < stringVal.length(); i++) {
                    try {
                        String charSym = String.valueOf(stringVal.charAt(i));

                        if (!hasDot && charSym.equals(".")) hasDot = true;
                        else Integer.parseInt(charSym);

                        result.append(charSym);
                    } catch (NumberFormatException e) {
                        if (result.isEmpty()) return new Value(0);
                    }
                }

                return new Value(Double.parseDouble(result.toString()));
            }
            case intVal -> {
                return new Value((double) intVal);
            }
            case floatVal -> {
                return this;
            }
            case arrayVal -> {
                return arrayVal.isEmpty() ? new Value(0) : new Value(1);
            }
            case boolVal -> {
                return new Value((boolVal ? 1 : 0));
            }
            case objectVal -> {
                return new Value(1);
            }
            default -> throw new RuntimeException("Unknown type");
        }
    }

    public Value toStringVal() {
        switch (typeVal) {
            case stringVal -> {
                return this;
            }
            case intVal -> {
                return new Value(String.valueOf(intVal));
            }
            case floatVal -> {
                return new Value(String.valueOf(floatVal));
            }
            case arrayVal -> {
                System.out.println("Warning: Array to string conversion");
                return new Value("Array");
            }
            case boolVal -> {
                return new Value(String.valueOf(boolVal ? 1 : 0));
            }
            case objectVal -> {
                return new Value(objVal.__toString());
            }
            default -> throw new RuntimeException("Unknown type");
        }
    }

    public Value toArray() {
        switch (typeVal) {
            case stringVal -> {
                return new Value(new HashMap<>(Map.of("0", new Value(stringVal))));
            }
            case intVal -> {
                return new Value(new HashMap<>(Map.of("0", new Value(intVal))));
            }
            case floatVal -> {
                return new Value(new HashMap<>(Map.of("0", new Value(floatVal))));
            }
            case arrayVal -> {
                return this;
            }
            case boolVal -> {
                return new Value(new HashMap<>(Map.of("0", new Value(boolVal))));
            }
            case objectVal -> {
                return new Value(objVal.__getValues());
            }
            default -> throw new RuntimeException("Unknown type");
        }
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
                return objVal.getClass().toString();
            }
            default -> throw new RuntimeException("Unknown type");
        }
    }
}
