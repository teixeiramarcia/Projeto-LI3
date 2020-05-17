package models;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Produtos implements IProdutos {
    private final Map<String, IProduto> produtos;

    public Produtos() {
        this.produtos = new HashMap<>();
    }

    @Override
    public boolean existeProduto(String productID) {
        return this.produtos.containsKey(productID);
    }

    @Override
    public void addProduct(IProduto IProduto) {
        this.produtos.put(IProduto.getProductID(), IProduto);
    }

    @Override
    public void updateProdutos(IVenda IVenda) {
        this.produtos.get(IVenda.getProductID()).updateProduto(IVenda);
    }

    @Override
    public List<String> getProductsNeverBought() {
        return this.produtos.values().stream()
                .filter(IProduto::wasntBoughtGeneral)
                .map(IProduto::getProductID)
                .sorted(String::compareTo)
                .collect(Collectors.toList());
    }

    @Override
    public List<Integer> getProductMonthlyBuyings(String productID) {
        return this.produtos.get(productID).getMonthlyBuyings();
    }

    @Override
    public List<Integer> getProductClients(String productID) {
        return this.produtos.get(productID).getClients();
    }

    @Override
    public List<Double> getProductBilling(String productID) {
        return this.produtos.get(productID).getTotalBilling();
    }
}