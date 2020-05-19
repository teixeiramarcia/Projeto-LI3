package models;

import utils.Pair;

import java.util.List;
import java.util.regex.Pattern;

public interface IProduto {
    Pattern pattern = Pattern.compile("[A-Z]{2}[1-9]\\d{3}");

    static boolean validaProduto(String line) {
        String pieces = line.trim();
        return IProduto.pattern.matcher(pieces).matches();
    }

    String getProductID();

    void updateProduto(IVenda IVenda);

    boolean wasntBoughtGeneral();

    List<Integer> getMonthlyBuyings();

    List<Integer> getClients();

    List<Double> getTotalBilling();

    int getDistinctClients();

    List<Pair<String, Double>> getTopNClients(int n);
}
