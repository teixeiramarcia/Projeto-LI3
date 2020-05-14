package models;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class GestVendas {
    private final Clientes clientes;
    private int clientes_lidos;
    private int clientes_validos;
    private final Produtos produtos;
    private int produtos_lidos;
    private int produtos_validos;
    private final Vendas vendas;
    private int vendas_lidas;
    private int vendas_validas;
    private final Filiais filiais;


    public GestVendas() {
        this.clientes = new Clientes();
        this.clientes_lidos = 0;
        this.clientes_validos = 0;
        this.produtos = new Produtos();
        this.produtos_lidos = 0;
        this.produtos_validos = 0;
        this.vendas = new Vendas();
        this.vendas_lidas = 0;
        this.vendas_validas = 0;
        this.filiais = new Filiais();
    }

    public void adicionaCliente(String clientID) {
        if(!Cliente.validaCliente(clientID)) {
            this.clientes_lidos++;
            return;
        }
        if(!this.clientes.existeCliente(clientID)) {
            Cliente cliente = new Cliente(clientID);
            this.clientes.addClient(cliente);
            this.clientes_validos++;
            this.clientes_lidos++;
        }
    }

    public void adicionaProduto(String productID) {
        if(!Produto.validaProduto(productID)) {
            this.produtos_lidos++;
            return;
        }
        if(!this.produtos.existeProduto(productID)) {
            Produto produto = new Produto(productID);
            this.produtos.addProduct(produto);
            this.produtos_validos++;
            this.produtos_lidos++;
        }
    }

    public void adicionaVenda(String venda_completa) {
        this.vendas.addVenda(venda_completa, this).ifPresent(v -> {
            this.vendas_validas++;
            this.clientes.updateClientes(v);
            this.produtos.updateProdutos(v);

            this.filiais.updateFiliais(v, this.clientes.getClient(v));
        });
        this.vendas_lidas++;
    }

    public boolean existeProduto(String piece) {
        return this.produtos.existeProduto(piece);
    }

    public boolean existeCliente(String piece) {
        return this.clientes.existeCliente(piece);
    }

    public int getTotalComprasMes(int mes) {
        return this.vendas.getTotalVendas(mes);
    }

    public Map<Integer, Double> getTotalFaturacaoMes(int mes) {
        Map<Integer, Double> resultado = new HashMap<>();
        for (int filial = 0; filial < 3; filial++)
            resultado.put(filial + 1, this.vendas.getTotalFaturacaoMesFilial(mes, filial));
        return resultado;
    }

    public Map<Integer, Integer> getTotalClientesMes(int mes) {
        Map<Integer, Integer> resultado = new HashMap<>();
        for (int filial = 0; filial < 3; filial++)
            resultado.put(filial + 1, this.clientes.getTotalClientesFilialMes(filial, mes));
        return resultado;
    }

    public List<String> getProdutosNComprados() {
        return this.produtos.getProductsNeverBought();
    }

    public int getNumClientesMes(int mes) {
        return getTotalClientesMes(mes).size();
    }

    public List<Integer> getClientMonthlyBuyings(String clientID) {
        return this.clientes.getClientMonthlyBuyings(clientID);
    }

    public List<Integer> getClientMonthlyProducts(String clientID) {
        return this.clientes.getClientMonthlyProducts(clientID);
    }

    public List<Double> getMonthlyTotalCost(String clientID) {
        return this.clientes.getMonthlyTotalCost(clientID);
    }

    public List<Integer> getProductMonthlyBuyings(String productID) {
        return this.produtos.getProductMonthlyBuyings(productID);
    }

    public List<Integer> getProductClients(String productID) {
        return this.produtos.getProductClients(productID);
    }

    public List<Double> getProductBilling(String productID) {
        return this.produtos.getProductBilling(productID);
    }

    public boolean produtoExiste(String productID) {
        return this.produtos.existeProduto(productID);
    }
}
