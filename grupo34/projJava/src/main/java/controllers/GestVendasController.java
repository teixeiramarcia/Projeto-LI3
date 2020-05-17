package controllers;

import models.GestVendas;
import models.ICliente;
import models.IGestVendas;
import models.IProduto;
import utils.Chrono;
import utils.Pair;
import views.Meses;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class GestVendasController implements IGestVendasController {
    private IGestVendas IGestVendas;

    private void readClients(String file, IGestVendas IGestVendas) throws FileNotFoundException {
        BufferedReader bf = new BufferedReader(new FileReader(file));
        Iterator<String> it = bf.lines().iterator();
        while (it.hasNext()) {
            String line = it.next();
            IGestVendas.adicionaCliente(line);
        }
    }

    private void readProducts(String file, IGestVendas IGestVendas) throws FileNotFoundException {
        BufferedReader bf = new BufferedReader(new FileReader(file));
        Iterator<String> it = bf.lines().iterator();
        while (it.hasNext()) {
            String line = it.next();
            IGestVendas.adicionaProduto(line);
        }
    }

    private void readVendas(String file, IGestVendas IGestVendas) throws FileNotFoundException {
        BufferedReader bf = new BufferedReader(new FileReader(file));
        Iterator<String> it = bf.lines().iterator();
        while (it.hasNext()) {
            String line = it.next();
            IGestVendas.adicionaVenda(line);
        }
    }

    @Override
    public void loadSGVFromFiles(String filesFolderPath) throws FileNotFoundException {
        this.IGestVendas = new GestVendas();
        Chrono.start();
        String ficheiro_clientes = filesFolderPath + "/Clientes.txt";
        readClients(ficheiro_clientes, IGestVendas);

        String ficheiro_produtos = filesFolderPath + "/Produtos.txt";
        readProducts(ficheiro_produtos, IGestVendas);

        String ficheiro_vendas = filesFolderPath + "/Vendas_1M.txt";
        readVendas(ficheiro_vendas, IGestVendas);

        Chrono.stop();
        System.out.println(Chrono.getTImeString());
    }

    @Override
    public Map<String, Integer> getTotalCompras() {
        Map<String, Integer> resultado = new HashMap<>();
        for (int mes = 0; mes < 12; mes++) {
            resultado.put(Meses.intToMes(mes), this.IGestVendas.getTotalComprasMes(mes));
        }
        return resultado;
    }

    @Override
    public Map<String, Map<Integer, Double>> getTotalFaturacao() {
        Map<String, Map<Integer, Double>> resultado = new HashMap<>();
        for (int mes = 0; mes < 12; mes++)
            resultado.put(Meses.intToMes(mes), this.IGestVendas.getTotalFaturacaoMes(mes));
        return resultado;
    }

    @Override
    public Map<String, Map<Integer, Integer>> getTotalClientesMesFilial() {
        Map<String, Map<Integer, Integer>> resultado = new HashMap<>();
        for (int mes = 0; mes < 12; mes++)
            resultado.put(Meses.intToMes(mes), this.IGestVendas.getTotalClientesMes(mes));
        return resultado;
    }

    @Override
    public List<String> getProdutosNuncaComprados() {
        return this.IGestVendas.getProdutosNComprados();
    }

    @Override
    public int getTotalVendas(int mes) {
        return this.IGestVendas.getTotalComprasMes(mes);
    }

    @Override
    public int getTotalClientes(int mes) {
        return this.IGestVendas.getNumClientesMes(mes);
    }

    @Override
    public List<Integer> getClientMonthlyBuyings(String clientID) {
        return this.IGestVendas.getClientMonthlyBuyings(clientID);
    }

    @Override
    public List<Integer> getClientMonthlyProducts(String clientID) {
        return this.IGestVendas.getClientMonthlyProducts(clientID);
    }

    @Override
    public List<Double> getMonthlyTotalCost(String clientID) {
        return this.IGestVendas.getMonthlyTotalCost(clientID);
    }

    @Override
    public List<Integer> getProductMonthlyBuyings(String productID) {
        return this.IGestVendas.getProductMonthlyBuyings(productID);
    }

    @Override
    public List<Integer> getProductClients(String productID) {
        return this.IGestVendas.getProductClients(productID);
    }

    @Override
    public List<Double> getProductBilling(String productID) {
        return this.IGestVendas.getProductBilling(productID);
    }

    @Override
    public boolean clienteValido(String clientID) {
        return ICliente.validaCliente(clientID);
    }

    @Override
    public boolean clienteExiste(String clientID) {
        return this.IGestVendas.existeCliente(clientID);
    }

    @Override
    public boolean produtoValido(String productID) {
        return IProduto.validaProduto(productID);
    }

    @Override
    public boolean produtoExiste(String productID) {
        return this.IGestVendas.produtoExiste(productID);
    }

    @Override
    public List<String> getClientFavoriteProducts(String clientID) {
        return this.IGestVendas.getClientFavoriteProducts(clientID);
    }

    @Override
    public List<Pair<String, Integer>> getTopNClients(int n) {
        return this.IGestVendas.getTopNClients(n);
    }
}
