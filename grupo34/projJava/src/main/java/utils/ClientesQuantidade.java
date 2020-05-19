package utils;

import views.Colors;

public class ClientesQuantidade {
    private final Pair<String, Integer> par;

    public ClientesQuantidade(Pair<String, Integer> par) {
        this.par = par;
    }

    @Override
    public String toString() {
        return Colors.YELLOW +
                "Cliente: " +
                Colors.RESET +
                par.getFirst() +
                "\n" +
                Colors.YELLOW +
                "Distintos: " +
                Colors.RESET +
                par.getSecond().toString() +
                "\n";
    }
}
