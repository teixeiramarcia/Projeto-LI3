package models;

import utils.Pair;
import views.Colors;

public class ClienteFaturacaoNoProduto extends Model implements IClienteFaturacaoNoProduto {
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
