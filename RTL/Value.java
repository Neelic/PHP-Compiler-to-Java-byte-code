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
    private boolean isRef = false;

    public Value(int intVal) {
        typeVal = TypeValue.intVal;
        this.intVal = intVal;
    }

    public Value(double floatVal) {
        typeVal = TypeValue.floatVal;
        this.floatVal = floatVal;
    }

    public Value(String stringVal) {
        typeVal = stringVal == null ? TypeValue.nullVal : TypeValue.stringVal;
        this.stringVal = stringVal;
    }

    public Value(boolean boolVal) {
        typeVal = TypeValue.boolVal;
        this.boolVal = boolVal;
    }

    public Value(HashMap<String, Value> arrayVal) {
        typeVal = arrayVal == null ? TypeValue.nullVal : TypeValue.arrayVal;
        this.arrayVal = arrayVal;
    }

    public Value(ObjValue objVal) {
        typeVal = objVal == null ? TypeValue.nullVal : TypeValue.objectVal;
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

    public boolean isRef() {
        return isRef;
    }

    public void setRef(boolean isRef) {
        this.isRef = isRef;
    }

    public void setRef(int isRef) {
        this.isRef = isRef > 0;
    }

    public void setArrayVal(HashMap<String, Value> arrayVal) {
        if (arrayVal == null) setNullVal();
        this.arrayVal = arrayVal;
    }

    public void setObjVal(ObjValue objVal) {
        if (objVal == null) setNullVal();
        this.objVal = objVal;
    }

    public void setNullVal() {
        typeVal = TypeValue.nullVal;
    }

    public Value add(Value other) {
        return addValue(other, false);
    }

    public Value add(int other) {
        return addValue(new Value(other), false);
    }

    public Value add(double other) {
        return addValue(new Value(other), false);
    }

    public Value add(String other) {
        return addValue(new Value(other), false);
    }

    public Value add(ObjValue other) {
        return addValue(new Value(other), false);
    }

    public Value concat(Value other) {
        return addValue(other.toStringVal(), true);
    }

    public Value concat(String other) {
        return addValue(new Value(other), true);
    }

    public Value concat(int other) {
        return addValue((new Value(other)).toStringVal(), true);
    }

    public Value concat(double other) {
        return addValue((new Value(other)).toStringVal(), true);
    }

    public Value concat(ObjValue other) {
        return addValue((new Value(other)).toStringVal(), true);
    }

    public Value concatTo(String other) {
        return (new Value(other)).toStringVal().addValue(this, true);
    }

    public Value concatTo(int other) {
        return (new Value(other)).toStringVal().addValue(this, true);
    }

    public Value concatTo(double other) {
        return (new Value(other)).toStringVal().addValue(this, true);
    }

    public Value concatTo(ObjValue other) {
        return (new Value(other)).toStringVal().addValue(this, true);
    }

    private Value addValue(Value other, boolean isConcat) {
        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        if (!isRef()) return new Value(intVal + other.getInt());

                        intVal += other.getInt();
                        return this;
                    }
                    case floatVal -> {
                        if (!isRef()) return new Value(intVal + other.getFloat());

                        typeVal = TypeValue.floatVal;
                        floatVal = intVal + other.getInt();
                        return this;
                    }
                    case boolVal -> {
                        if (!isRef()) return new Value(intVal + (other.getBool() ? 1 : 0));

                        intVal += other.getBool() ? 1 : 0;
                        return this;
                    }
                    case nullVal -> {
                        if (!isRef()) return new Value(intVal);

                        return this;
                    }
                    case stringVal -> {
                        Value newVal = other.toFloatVal();

                        if (newVal.typeVal != TypeValue.nullVal) return addValue(newVal, isConcat);
                    }
                }
            }
            case floatVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        if (!isRef()) return new Value(floatVal + other.getInt());

                        floatVal += other.getInt();
                        return this;
                    }
                    case floatVal -> {
                        if (!isRef()) return new Value(floatVal + other.getFloat());

                        floatVal += other.getFloat();
                        return this;
                    }
                    case boolVal -> {
                        if (!isRef()) return new Value(floatVal - (other.getBool() ? 1 : 0));

                        floatVal -= other.getBool() ? 1 : 0;
                        return this;
                    }
                    case nullVal -> {
                        if (!isRef()) return new Value(floatVal);

                        return this;
                    }
                    case stringVal -> {
                        Value newVal = other.toFloatVal();

                        if (newVal.typeVal != TypeValue.nullVal) return addValue(newVal, isConcat);
                    }
                }
            }
            case stringVal -> {
                if (isConcat) {
                    switch (other.getType()) {
                        case intVal -> {
                            if (!isRef()) return new Value(stringVal + other.getInt());

                            stringVal += other.getInt();
                            return this;
                        }
                        case floatVal -> {
                            if (!isRef()) return new Value(stringVal + other.getFloat());

                            stringVal += other.getFloat();
                            return this;
                        }
                        case boolVal -> {
                            if (!isRef()) return new Value(stringVal + (other.getBool() ? 1 : 0));

                            stringVal += other.getBool() ? 1 : 0;
                            return this;
                        }
                        case stringVal -> {
                            if (!isRef()) return new Value(stringVal + other.getString());

                            stringVal += other.getString();
                            return this;
                        }
                        case nullVal -> {
                            if (!isRef()) return new Value(stringVal);

                            return this;
                        }
                    }
                } else {
                    Value newVal = this.toFloatVal();

                    if (newVal.getType() != TypeValue.nullVal) {
                        try {
                            Double.parseDouble(stringVal);
                        } catch (NumberFormatException e) {
                            System.out.println("Warning: A non numeric value encountered");
                        }

                        return addValue(newVal, false);
                    }
                }
            }
            case boolVal -> {
                switch (other.getType()) {
                    case boolVal -> {
                        if (!isRef()) return new Value((boolVal ? 1 : 0) + (other.getBool() ? 1 : 0));

                        typeVal = TypeValue.intVal;
                        intVal = (boolVal ? 1 : 0) + (other.getBool() ? 1 : 0);
                        return this;
                    }
                    case intVal -> {
                        if (!isRef()) return new Value((boolVal ? 1 : 0) + other.getInt());

                        typeVal = TypeValue.intVal;
                        intVal = (boolVal ? 1 : 0) + other.getInt();
                        return this;
                    }
                    case floatVal -> {
                        if (!isRef()) return new Value((boolVal ? 1 : 0) + other.getFloat());

                        typeVal = TypeValue.floatVal;
                        floatVal = (boolVal ? 1 : 0) + other.getFloat();
                        return this;
                    }
                    case nullVal -> {
                        if (!isRef()) return new Value((boolVal ? 1 : 0));

                        return this;
                    }
                    case stringVal -> {
                        Value newVal = other.toFloatVal();

                        if (newVal.typeVal != TypeValue.nullVal) return addValue(newVal, isConcat);
                    }
                }
            }
            case nullVal -> {
                return this.toIntVal().addValue(other, isConcat);
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
        if (other == null) other = new Value((ObjValue) null);

        switch (typeVal) {
            case intVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        if (!isRef()) return new Value(intVal - other.getInt());

                        intVal -= other.getInt();
                        return this;
                    }
                    case floatVal -> {
                        if (!isRef()) return new Value(intVal - other.getFloat());

                        typeVal = TypeValue.floatVal;
                        floatVal = intVal - other.getFloat();
                        return this;
                    }
                    case boolVal -> {
                        if (!isRef()) return new Value(intVal - (other.getBool() ? 1 : 0));

                        intVal -= (other.getBool() ? 1 : 0);
                        return this;
                    }
                    case nullVal -> {
                        if (!isRef()) return new Value(intVal);

                        return this;
                    }
                    case stringVal -> {
                        Value newVal = other.toFloatVal();

                        if (newVal.typeVal != TypeValue.nullVal) return sub(newVal);
                    }
                }
            }
            case floatVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        if (!isRef()) return new Value(floatVal - other.getInt());

                        floatVal -= other.getInt();
                        return this;
                    }
                    case floatVal -> {
                        if (!isRef()) return new Value(floatVal - other.getFloat());

                        floatVal -= other.getFloat();
                        return this;
                    }
                    case boolVal -> {
                        if (!isRef()) return new Value(floatVal - (other.getBool() ? 1 : 0));

                        floatVal -= (other.getBool() ? 1 : 0);
                        return this;
                    }
                    case nullVal -> {
                        if (!isRef()) return new Value(floatVal);

                        return this;
                    }
                    case stringVal -> {
                        Value newVal = other.toFloatVal();

                        if (newVal.typeVal != TypeValue.nullVal) return sub(newVal);
                    }
                }
            }
            case boolVal -> {
                switch (other.getType()) {
                    case intVal -> {
                        if (!isRef()) return new Value((boolVal ? 1 : 0) - other.getInt());

                        typeVal = TypeValue.intVal;
                        intVal = (boolVal ? 1 : 0) - other.getInt();
                        return this;
                    }
                    case floatVal -> {
                        if (!isRef()) return new Value((boolVal ? 1 : 0) - other.getFloat());

                        typeVal = TypeValue.floatVal;
                        floatVal = (boolVal ? 1 : 0) - other.getFloat();
                        return this;
                    }
                    case boolVal -> {
                        if (!isRef()) return new Value((boolVal ? 1 : 0) - (other.getBool() ? 1 : 0));

                        typeVal = TypeValue.intVal;
                        intVal = (boolVal ? 1 : 0) - (other.getBool() ? 1 : 0);
                        return this;
                    }
                    case nullVal -> {
                        if (!isRef()) return new Value((boolVal ? 1 : 0));

                        return this;
                    }
                    case stringVal -> {
                        Value newVal = other.toFloatVal();

                        if (newVal.typeVal != TypeValue.nullVal) return sub(newVal);
                    }
                }
            }
            case nullVal -> {
                return this.toIntVal().sub(other);
            }
            case stringVal -> {
                Value newVal = this.toFloatVal();

                if (newVal.getType() != TypeValue.nullVal) {
                    try {
                        Double.parseDouble(stringVal);
                    } catch (NumberFormatException e) {
                        System.out.println("Warning: A non numeric value encountered");
                    }

                    return sub(newVal);
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
            System.out.println("Warning: Trying to access array offset on value of type " + typeToString());
        } else if (typeVal == TypeValue.stringVal) {
            int ind;

            try {
                ind = Integer.parseInt(index);
            } catch (NumberFormatException e) {
                System.out.println("Warning: String offset cast occurred");
                return new Value((ObjValue) null);
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

        if (!arrayVal.containsKey(index)) return new Value((ObjValue) null);

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
                        if (result.isEmpty()) return new Value((ObjValue) null);
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
            case nullVal -> {
                return new Value(0);
            }
            default -> throw new RuntimeException("Unknown type");
        }
    }

    public Value toFloatVal() {
        switch (typeVal) {
            case stringVal -> {
                StringBuilder result = new StringBuilder();
                boolean hasDot = false;
                boolean hasNumberAfterDot = false;
                for (int i = 0; i < stringVal.length(); i++) {
                    try {
                        String charSym = String.valueOf(stringVal.charAt(i));

                        if (!hasDot && charSym.equals(".")) hasDot = true;
                        else {
                            Integer.parseInt(charSym);

                            if (hasDot) hasNumberAfterDot = true;
                        }

                        result.append(charSym);
                    } catch (NumberFormatException e) {
                        if (result.isEmpty()) return new Value((ObjValue) null);
                    }
                }

                return hasNumberAfterDot
                        ? new Value(Double.parseDouble(result.toString()))
                        : new Value(Integer.parseInt(result.toString()));
            }
            case intVal -> {
                return new Value((double) intVal);
            }
            case floatVal -> {
                return this;
            }
            case arrayVal -> {
                return arrayVal.isEmpty() ? new Value(0.) : new Value(1.);
            }
            case boolVal -> {
                return new Value((boolVal ? 1. : 0.));
            }
            case objectVal -> {
                return new Value(1.);
            }
            case nullVal -> {
                return new Value(0.);
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
            case nullVal -> {
                return new Value(String.valueOf(0));
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
            case nullVal -> {
                return new Value(new HashMap<>());
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
            case nullVal -> {
                return "null";
            }
            default -> throw new RuntimeException("Unknown type");
        }
    }
}
