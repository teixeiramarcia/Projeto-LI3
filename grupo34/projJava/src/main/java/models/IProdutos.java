package models;

import utils.Pair;

import java.util.List;

public interface IProdutos {
    boolean existeProduto(String productID);

    void addProduct(IProduto IProduto);

    void updateProdutos(IVenda IVenda);

    List<String> getProductsNeverBought();

    List<Integer> getProductMonthlyBuyings(String productID);

    List<Integer> getProductClients(String productID);

    List<Double> getProductBilling(String productID);

    List<Pair<String, Integer>> getTopNProducts(int n);

    List<Pair<String, Double>> getTopNClientsOfProduct(String productID, int n);
}
