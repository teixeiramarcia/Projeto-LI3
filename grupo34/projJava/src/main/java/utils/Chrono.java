package utils;

import static java.lang.System.nanoTime;

public class Chrono {

    private static long inicio = 0L;
    private static long fim = 0L;
    private static long elapsedTime = 0L;


    public static void start() {
        fim = 0L;
        inicio = nanoTime();
    }

    public static void stop() {
        fim = nanoTime();
        elapsedTime = fim - inicio;
    }

    public static String getTImeString() {
        return "Elapsed Time: " + (elapsedTime / 1.0E09) + " s";
    }
}
