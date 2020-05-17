package models;

import utils.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class GestVendas implements IGestVendas {
    private final IClientes IClientes;
    private final IProdutos IProdutos;
    private final IVendas IVendas;
    private final IFiliais IFiliais;
    private int clientes_lidos;
    private int clientes_validos;
    private int produtos_lidos;
    private int produtos_validos;
    private int vendas_lidas;
    private int vendas_validas;


    public GestVendas() {
        this.IClientes = new Clientes();
        this.clientes_lidos = 0;
        this.clientes_validos = 0;
        this.IProdutos = new Produtos();
        this.produtos_lidos = 0;
        this.produtos_validos = 0;
        this.IVendas = new Vendas();
        this.vendas_lidas = 0;
        this.vendas_validas = 0;
        this.IFiliais = new Filiais();
    }

    @Override
    public void adicionaCliente(String clientID) {
        if (!ICliente.validaCliente(clientID)) {
            this.clientes_lidos++;
            return;
        }
        if (!this.IClientes.existeCliente(clientID)) {
            ICliente ICliente = new Cliente(clientID);
            this.IClientes.addClient(ICliente);
            this.clientes_validos++;
            this.clientes_lidos++;
        }
    }

    @Override
    public void adicionaProduto(String productID) {
        if (!IProduto.validaProduto(productID)) {
            this.produtos_lidos++;
            return;
        }
        if (!this.IProdutos.existeProduto(productID)) {
            IProduto IProduto = new Produto(productID);
            this.IProdutos.addProduct(IProduto);
            this.produtos_validos++;
            this.produtos_lidos++;
        }
    }

    @Override
    public void adicionaVenda(String venda_completa) {
        this.IVendas.addVenda(venda_completa, this).ifPresent(v -> {
            this.vendas_validas++;
            this.IClientes.updateClientes(v);
            this.IProdutos.updateProdutos(v);

            this.IFiliais.updateFiliais(v, this.IClientes.getClient(v));
        });
        this.vendas_lidas++;
    }

    @Override
    public boolean existeProduto(String piece) {
        return this.IProdutos.existeProduto(piece);
    }

    @Override
    public boolean existeCliente(String piece) {
        return this.IClientes.existeCliente(piece);
    }

    @Override
    public int getTotalComprasMes(int mes) {
        return this.IVendas.getTotalVendas(mes);
    }

    @Override
    public Map<Integer, Double> getTotalFaturacaoMes(int mes) {
        Map<Integer, Double> resultado = new HashMap<>();
        for (int filial = 0; filial < 3; filial++)
            resultado.put(filial + 1, this.IVendas.getTotalFaturacaoMesFilial(mes, filial));
        return resultado;
    }

    @Override
    public Map<Integer, Integer> getTotalClientesMes(int mes) {
        Map<Integer, Integer> resultado = new HashMap<>();
        for (int filial = 0; filial < 3; filial++)
            resultado.put(filial + 1, this.IClientes.getTotalClientesFilialMes(filial, mes));
        return resultado;
    }

    @Override
    public List<String> getProdutosNComprados() {
        return this.IProdutos.getProductsNeverBought();
    }

    @Override
    public int getNumClientesMes(int mes) {
        return getTotalClientesMes(mes).size();
    }

    @Override
    public List<Integer> getClientMonthlyBuyings(String clientID) {
        return this.IClientes.getClientMonthlyBuyings(clientID);
    }

    @Override
    public List<Integer> getClientMonthlyProducts(String clientID) {
        return this.IClientes.getClientMonthlyProducts(clientID);
    }

    @Override
    public List<Double> getMonthlyTotalCost(String clientID) {
        return this.IClientes.getMonthlyTotalCost(clientID);
    }

    @Override
    public List<Integer> getProductMonthlyBuyings(String productID) {
        return this.IProdutos.getProductMonthlyBuyings(productID);
    }

    @Override
    public List<Integer> getProductClients(String productID) {
        return this.IProdutos.getProductClients(productID);
    }

    @Override
    public List<Double> getProductBilling(String productID) {
        return this.IProdutos.getProductBilling(productID);
    }

    @Override
    public boolean produtoExiste(String productID) {
        return this.IProdutos.existeProduto(productID);
    }

    @Override
    public List<String> getClientFavoriteProducts(String clientID) {
        return this.IClientes.getClientFavoriteProducts(clientID);
    }

    @Override
    public List<Pair<String, Integer>> getTopNClients(int n) {
        return this.IClientes.getTopNClients(n);
    }
}
