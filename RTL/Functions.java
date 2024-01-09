class Functions {
    public void echo(Value value) {
        if (value == null) return;
        System.out.println(value.toStringVal().getString());
    }

    public void echo(String value) {
        if (value == null) return;
        System.out.println(value);
    }
}
