package models;

import java.util.List;
import java.util.Map;
import java.util.regex.Pattern;

public interface ICliente {
    Pattern pattern = Pattern.compile("[A-Z]([1-4]\\d{3}|5000)");

    static boolean validaCliente(String line) {
        return ICliente.pattern.matcher(line.trim()).matches();
    }

    String getClientID();

    double getFaturacaoFilial(int filial);

    void updateCliente(IVenda IVenda);

    boolean comprouNoMesEFilial(int mes, int filial);

    boolean comprouNoMes(int mes);

    List<Integer> getMonthlyBuyings();

    List<Integer> getMonthlyProducts();

    List<Double> getMonthlyTotalCost();

    List<String> getFavoriteProducts();

    Map<String, Integer> getProdutosPorQuantidade();

    int getDistinctProducts();
}
