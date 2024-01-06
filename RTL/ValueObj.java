final class ValueObj extends Val {
    ValueObj() {
        typeVal = Type.objectVal;
    }

    public void addToArray(Val other) {
        throw new RuntimeException("Fatal error: Uncaught Error: cannot use object of type a as array");
    }

    @Override
    public int getInt() {
        throw new RuntimeException("");
    }

    @Override
    public double getFloat() {
        throw new RuntimeException("");
    }

    @Override
    public String getString() {
        throw new RuntimeException("");
    }

    @Override
    public boolean isBool() {
        throw new RuntimeException("");
    }
}
