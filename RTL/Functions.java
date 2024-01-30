package RTL;

import java.util.Scanner;

public class Functions {
    public static void echo(Value value) {
        if (value == null) return;
        System.out.print(value.toStringVal().getString());
    }

    public static void echo(String value) {
        if (value == null) return;
        System.out.print(value);
    }

    public static void echo(int value) {
        System.out.print(value);
    }

    public static void echo(float value) {
        System.out.print(value);
    }

    public static void echo(boolean value) {
        System.out.print(value);
    }

    public static void print(Value value) {
        if (value == null) return;
        System.out.print(value.toStringVal().getString());
    }

    public static void print(String value) {
        if (value == null) return;
        System.out.print(value);
    }

    public static void print(int value) {
        System.out.print(value);
    }

    public static void print(float value) {
        System.out.print(value);
    }

    public static void print(boolean value) {
        System.out.print(value);
    }

    public static Value readline() {
        Scanner in = new Scanner(System.in);
        return new Value(in.nextLine());
    }
}
