package RTL;

public class FatalError extends RuntimeException {
    FatalError(String message) {
        super(message);
    }
}
