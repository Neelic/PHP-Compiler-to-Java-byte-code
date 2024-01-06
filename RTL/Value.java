import java.util.HashMap;

class Value extends Val {
    private int intVal;

    private double floatVal;

    private String stringVal;
    private boolean boolVal;
    private final HashMap<String, Val> arrayVal = new HashMap<>();
    private int lastArrayIndex = 0;

    public Value(int intVal) {
        typeVal = Type.intVal;
        this.intVal = intVal;
    }

    public Value(double floatVal) {
        typeVal = Type.floatVal;
        this.floatVal = floatVal;
    }

    public Value(String stringVal) {
        typeVal = Type.stringVal;
        this.stringVal = stringVal;
    }

    public Value(boolean boolVal) {
        typeVal = Type.boolVal;
        this.boolVal = boolVal;
    }

    public Value() {
        typeVal = Type.arrayVal;
    }

    public int getInt() {
        return intVal;
    }

    public double getFloat() {
        return floatVal;
    }

    public String getString() {
        return stringVal;
    }

    public boolean isBool() {
        return boolVal;
    }

    public HashMap<String, Val> getArrayVal() {
        return arrayVal;
    }

    public Val add(Val other) {
        if (typeVal == Type.intVal) {
            if (other.getType() == Type.intVal) {
                return new Value(intVal + other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(intVal + other.getFloat());
            }
        } else if (typeVal == Type.floatVal) {
            if (other.getType() == Type.intVal) {
                return new Value(floatVal + other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(floatVal + other.getFloat());
            }
        }

        System.out.println();
        throw new RuntimeException("");
    }

    public Val sub(Val other) {
        if (typeVal == Type.intVal) {
            if (other.getType() == Type.intVal) {
                return new Value(intVal - other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(intVal - other.getFloat());
            }
        } else if (typeVal == Type.floatVal) {
            if (other.getType() == Type.intVal) {
                return new Value(floatVal - other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(floatVal - other.getFloat());
            }
        }

        System.out.println();
        throw new RuntimeException("");
    }

    public Val mul(Val other) {
        if (typeVal == Type.intVal) {
            if (other.getType() == Type.intVal) {
                return new Value(intVal * other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(intVal * other.getFloat());
            }
        } else if (typeVal == Type.floatVal) {
            if (other.getType() == Type.intVal) {
                return new Value(floatVal * other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(floatVal * other.getFloat());
            }
        }

        System.out.println();
        throw new RuntimeException("");
    }

    public Val div(Val other) {
        if (typeVal == Type.intVal) {
            if (other.getType() == Type.intVal) {
                return new Value(intVal / other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(intVal / other.getFloat());
            }
        } else if (typeVal == Type.floatVal) {
            if (other.getType() == Type.intVal) {
                return new Value(floatVal / other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(floatVal / other.getFloat());
            }
        }

        System.out.println();
        throw new RuntimeException("");
    }

    public Val mod(Val other) {
        if (typeVal == Type.intVal) {
            if (other.getType() == Type.intVal) {
                return new Value(intVal % other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(intVal % other.getFloat());
            }
        } else if (typeVal == Type.floatVal) {
            if (other.getType() == Type.intVal) {
                return new Value(floatVal % other.getInt());
            } else if (other.getType() == Type.floatVal) {
                return new Value(floatVal % other.getFloat());
            }
        }

        System.out.println();
        throw new RuntimeException("");
    }

    public void addToArray(String index, Val other) {
        if (typeVal != Type.arrayVal) {
            throw new RuntimeException("Fatal error: Uncaught Error: cannot use a scalar value as an array");
        }

        arrayVal.put(index, other);

        try {
            int ind = Integer.parseInt(index);

            if (ind > lastArrayIndex) lastArrayIndex = ind;
        } catch (NumberFormatException e) {
            return;
        }
    }

    public void addToArray(Val other) {
        if (typeVal == Type.stringVal) {
            throw new RuntimeException("Fatal error: Uncaught Error: [] operator not supported for strings");
        }

        addToArray(String.valueOf(++lastArrayIndex), other);
    }

    public Val getArrayVal(String index) {
        if (typeVal != Type.arrayVal && typeVal != Type.stringVal) {
            String type = "";
            switch (typeVal) {
                case intVal -> type = "int";
                case boolVal -> type = "bool";
                case floatVal -> type = "float";
            }
            System.out.println("Warning: Trying to access array offset on value of type " + type);
        } else if (typeVal == Type.stringVal) {
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

    public Val toIntVal() {
        return null;
    }

    public Val toFloatVal() {
        return null;
    }

    public Val toStringVal() {
        return null;
    }

    public Val toArray() {
        return null;
    }

    public Val toObject() {
        return null;
    }
}
