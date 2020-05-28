package models;

import utils.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * {@inheritDoc}
 */

public class GestVendas extends Model implements IGestVendas {
    private final IClientes clientes;
    private final IProdutos produtos;
    private final IVendas vendas;
    private final IFiliais filiais;
    private int clientes_lidos;
    private int clientes_validos;
    private int produtos_lidos;
    private int produtos_validos;
    private int vendas_lidas;
    private int vendas_validas;


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

    @Override
    public void adicionaCliente(String clientID) {
        if (!ICliente.validaCliente(clientID)) {
            this.clientes_lidos++;
            return;
        }
        if (!this.clientes.existeCliente(clientID)) {
            ICliente ICliente = new Cliente(clientID);
            this.clientes.addClient(ICliente);
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
        if (!this.produtos.existeProduto(productID)) {
            IProduto IProduto = new Produto(productID);
            this.produtos.addProduct(IProduto);
            this.produtos_validos++;
            this.produtos_lidos++;
        }
    }

    @Override
    public void adicionaVenda(String venda_completa) {
        this.vendas.addVenda(venda_completa, this).ifPresent(v -> {
            this.vendas_validas++;
            this.clientes.updateClientes(v);
            this.produtos.updateProdutos(v);

            this.filiais.updateFiliais(v, this.clientes.getClient(v));
        });
        this.vendas_lidas++;
    }

    @Override
    public boolean existeProduto(String piece) {
        return this.produtos.existeProduto(piece);
    }

    @Override
    public boolean existeCliente(String piece) {
        return this.clientes.existeCliente(piece);
    }

    @Override
    public int getWrongSales() {
        return this.vendas_lidas - this.vendas_validas;
    }

    @Override
    public int getTotalProducts() {
        return this.produtos_validos;
    }

    @Override
    public int getTotalDistinctBoughtProducts() {
        return this.vendas.getDistinctProducts();
    }

    @Override
    public int getTotalNeverBoughtProducts() {
        return this.produtos.getProductsNeverBought().size();
    }

    @Override
    public int getTotalClients() {
        return this.clientes_validos;
    }

    @Override
    public int getTotalBuyingClients() {
        return this.vendas.getTotalBuyingClients();
    }

    @Override
    public int getNeverBuyingClients() {
        return this.clientes_validos - getTotalBuyingClients();
    }

    @Override
    public int getZeroSales() {
        return this.vendas.getZeroSales();
    }

    @Override
    public double getTotalBilling() {
        return this.vendas.getTotalBilling();
    }

    @Override
    public int getTotalComprasMes(int mes) {
        return this.vendas.getTotalVendas(mes);
    }

    @Override
    public Map<Integer, Double> getTotalFaturacaoMes(int mes) {
        Map<Integer, Double> resultado = new HashMap<>();
        for (int filial = 0; filial < 3; filial++)
            resultado.put(filial + 1, this.vendas.getTotalFaturacaoMesFilial(mes, filial));
        return resultado;
    }

    @Override
    public Map<Integer, Integer> getTotalClientesMes(int mes) {
        Map<Integer, Integer> resultado = new HashMap<>();
        for (int filial = 0; filial < 3; filial++)
            resultado.put(filial + 1, this.clientes.getTotalClientesFilialMes(filial, mes));
        return resultado;
    }

    @Override
    public List<String> getProdutosNComprados() {
        return this.produtos.getProductsNeverBought();
    }

    @Override
    public int getNumClientesCompraramNoMes(int mes) {
        return this.clientes.getTotalClientesMes(mes);
    }

    @Override
    public List<Integer> getClientMonthlyBuyings(String clientID) {
        return this.clientes.getClientMonthlyBuyings(clientID);
    }

    @Override
    public List<Integer> getClientMonthlyProducts(String clientID) {
        return this.clientes.getClientMonthlyProducts(clientID);
    }

    @Override
    public List<Double> getMonthlyTotalCost(String clientID) {
        return this.clientes.getMonthlyTotalCost(clientID);
    }

    @Override
    public List<Integer> getProductMonthlyBuyings(String productID) {
        return this.produtos.getProductMonthlyBuyings(productID);
    }

    @Override
    public List<Integer> getProductClients(String productID) {
        return this.produtos.getProductClients(productID);
    }

    @Override
    public List<Double> getProductBilling(String productID) {
        return this.produtos.getProductBilling(productID);
    }

    @Override
    public boolean produtoExiste(String productID) {
        return this.produtos.existeProduto(productID);
    }

    @Override
    public List<String> getClientFavoriteProducts(String clientID) {
        return this.clientes.getClientFavoriteProducts(clientID);
    }

    @Override
    public List<Pair<String, Integer>> getTopNClients(int n) {
        return this.clientes.getTopNClients(n);
    }

    @Override
    public List<Pair<String, Integer>> getTopNProducts(int n) {
        return this.produtos.getTopNProducts(n);
    }

    @Override
    public String[][] getTop3Buyers() {
        return this.filiais.getTop3Buyers();
    }

    @Override
    public List<Pair<String, Double>> getTopNClientsOfProduct(String productID, int n) {
        return this.produtos.getTopNClientsOfProduct(productID, n);
    }

    @Override
    public List<Pair<String, List<Double>>> getFaturacaoPorProduto() {
        return this.produtos.getFaturacaoPorProduto();
    }
}
