package utils;

import views.Colors;

import java.util.function.Supplier;

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

    public static String getTimeString() {
        return Colors.YELLOW + "\nElapsed Time: " + Colors.RESET + (elapsedTime / 1.0E09) + " s\n\n";
    }

    public static <T> Pair<T, String> chronoMe(Supplier<T> s) {
        start();
        T resultado = s.get();
        stop();
        return Pair.of(resultado, getTimeString());
    }
}
