package models;

import java.util.*;

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
}
