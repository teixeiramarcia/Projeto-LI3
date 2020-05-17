package models;

import java.util.List;

public interface IProdutos {
    boolean existeProduto(String productID);

    void addProduct(IProduto IProduto);

    void updateProdutos(IVenda IVenda);

    List<String> getProductsNeverBought();

    List<Integer> getProductMonthlyBuyings(String productID);

    List<Integer> getProductClients(String productID);

    List<Double> getProductBilling(String productID);
}
