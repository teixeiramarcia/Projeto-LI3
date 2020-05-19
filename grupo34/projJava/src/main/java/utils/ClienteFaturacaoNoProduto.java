package utils;

import views.Colors;

public class ClienteFaturacaoNoProduto {
    private final Pair<String, Double> par;

    public ClienteFaturacaoNoProduto(Pair<String, Double> par) {
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
                "Faturação: " +
                Colors.RESET +
                par.getSecond().toString() +
                "\n";
    }
}
