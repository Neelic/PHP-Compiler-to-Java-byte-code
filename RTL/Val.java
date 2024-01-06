abstract class Val {
    protected Type typeVal;

    public Type getType() {
        return typeVal;
    }

    public abstract int getInt();

    public abstract double getFloat();

    public abstract String getString();

    public abstract boolean isBool();
}
