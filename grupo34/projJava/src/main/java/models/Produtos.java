package models;

import java.util.*;
import java.util.stream.Collectors;

public class Produtos {
    private final Map<String, Produto> produtos;

    public Produtos() {
        this.produtos = new HashMap<>();
    }

    public boolean existeProduto(String productID) {
        return this.produtos.containsKey(productID);
    }

    public void addProduct(Produto produto) {
        this.produtos.put(produto.getProductID(), produto);
    }

    public void updateProdutos(Venda venda) {
        this.produtos.get(venda.getProductID()).updateProduto(venda);
    }

    public List<String> getProductsNeverBought() {
        return this.produtos.values().stream()
                .filter(Produto::wasntBoughtGeneral)
                .map(Produto::getProductID)
                .sorted(String::compareTo)
                .collect(Collectors.toList());
    }

    public List<Integer> getProductMonthlyBuyings(String productID) {
        return this.produtos.get(productID).getMonthlyBuyings();
    }

    public List<Integer> getProductClients(String productID) {
        return this.produtos.get(productID).getClients();
    }

    public List<Double> getProductBilling(String productID) {
        return this.produtos.get(productID).getTotalBilling();
    }
}
