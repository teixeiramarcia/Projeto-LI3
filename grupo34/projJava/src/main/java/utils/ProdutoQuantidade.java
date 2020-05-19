package utils;

import views.Colors;

public class ProdutoQuantidade {
    private final Pair<String, Integer> par;

    public ProdutoQuantidade(Pair<String, Integer> par) {
        this.par = par;
    }

    @Override
    public String toString() {
        return Colors.YELLOW +
                "Produto: " +
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
