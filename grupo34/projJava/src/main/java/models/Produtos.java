package models;

import utils.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Produtos extends Model implements IProdutos {
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

    public List<Pair<String, Integer>> getTopNProducts(int n) {
        Stream<Pair<String, Integer>> s = this.produtos.values().stream()
                .map(produto -> Pair.of(produto.getProductID(), produto.getDistinctClients()));
        return s.sorted((par1, par2) -> par2.getSecond() - par1.getSecond())
                .limit(n)
                .collect(Collectors.toList());
    }

    @Override
    public List<Pair<String, Double>> getTopNClientsOfProduct(String productID, int n) {
        return this.produtos.get(productID).getTopNClients(n);
    }

    @Override
    public List<Pair<String, List<Double>>> getFaturacaoPorProduto() {
        return this.produtos.values().stream()
                .map(IProduto::getFaturacaoMesFilial)
                .collect(Collectors.toList());
    }
}