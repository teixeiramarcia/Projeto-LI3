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
    private IGestVendas gestVendas;

    private void readClients(String file, IGestVendas gestVendas) throws FileNotFoundException {
        BufferedReader bf = new BufferedReader(new FileReader(file));
        Iterator<String> it = bf.lines().iterator();
        while (it.hasNext()) {
            String line = it.next();
            gestVendas.adicionaCliente(line);
        }
    }

    private void readProducts(String file, IGestVendas gestVendas) throws FileNotFoundException {
        BufferedReader bf = new BufferedReader(new FileReader(file));
        Iterator<String> it = bf.lines().iterator();
        while (it.hasNext()) {
            String line = it.next();
            gestVendas.adicionaProduto(line);
        }
    }

    private void readVendas(String file, IGestVendas gestVendas) throws FileNotFoundException {
        BufferedReader bf = new BufferedReader(new FileReader(file));
        Iterator<String> it = bf.lines().iterator();
        while (it.hasNext()) {
            String line = it.next();
            gestVendas.adicionaVenda(line);
        }
    }

    @Override
    public void loadSGVFromFiles(String filesFolderPath) throws FileNotFoundException {
        this.gestVendas = new GestVendas();
        Chrono.start();
        String ficheiro_clientes = filesFolderPath + "/Clientes.txt";
        readClients(ficheiro_clientes, gestVendas);

        String ficheiro_produtos = filesFolderPath + "/Produtos.txt";
        readProducts(ficheiro_produtos, gestVendas);

        String ficheiro_vendas = filesFolderPath + "/Vendas_1M.txt";
        readVendas(ficheiro_vendas, gestVendas);

        Chrono.stop();
        System.out.println(Chrono.getTImeString());
    }

    @Override
    public Map<String, Integer> getTotalCompras() {
        Map<String, Integer> resultado = new HashMap<>();
        for (int mes = 0; mes < 12; mes++) {
            resultado.put(Meses.intToMes(mes), this.gestVendas.getTotalComprasMes(mes));
        }
        return resultado;
    }

    @Override
    public Map<String, Map<Integer, Double>> getTotalFaturacao() {
        Map<String, Map<Integer, Double>> resultado = new HashMap<>();
        for (int mes = 0; mes < 12; mes++)
            resultado.put(Meses.intToMes(mes), this.gestVendas.getTotalFaturacaoMes(mes));
        return resultado;
    }

    @Override
    public Map<String, Map<Integer, Integer>> getTotalClientesMesFilial() {
        Map<String, Map<Integer, Integer>> resultado = new HashMap<>();
        for (int mes = 0; mes < 12; mes++)
            resultado.put(Meses.intToMes(mes), this.gestVendas.getTotalClientesMes(mes));
        return resultado;
    }

    @Override
    public List<String> getProdutosNuncaComprados() {
        return this.gestVendas.getProdutosNComprados();
    }

    @Override
    public int getTotalVendas(int mes) {
        return this.gestVendas.getTotalComprasMes(mes);
    }

    @Override
    public int getTotalClientes(int mes) {
        return this.gestVendas.getNumClientesMes(mes);
    }

    @Override
    public List<Integer> getClientMonthlyBuyings(String clientID) {
        return this.gestVendas.getClientMonthlyBuyings(clientID);
    }

    @Override
    public List<Integer> getClientMonthlyProducts(String clientID) {
        return this.gestVendas.getClientMonthlyProducts(clientID);
    }

    @Override
    public List<Double> getMonthlyTotalCost(String clientID) {
        return this.gestVendas.getMonthlyTotalCost(clientID);
    }

    @Override
    public List<Integer> getProductMonthlyBuyings(String productID) {
        return this.gestVendas.getProductMonthlyBuyings(productID);
    }

    @Override
    public List<Integer> getProductClients(String productID) {
        return this.gestVendas.getProductClients(productID);
    }

    @Override
    public List<Double> getProductBilling(String productID) {
        return this.gestVendas.getProductBilling(productID);
    }

    @Override
    public boolean clienteValido(String clientID) {
        return ICliente.validaCliente(clientID);
    }

    @Override
    public boolean clienteExiste(String clientID) {
        return this.gestVendas.existeCliente(clientID);
    }

    @Override
    public boolean produtoValido(String productID) {
        return IProduto.validaProduto(productID);
    }

    @Override
    public boolean produtoExiste(String productID) {
        return this.gestVendas.produtoExiste(productID);
    }

    @Override
    public List<String> getClientFavoriteProducts(String clientID) {
        return this.gestVendas.getClientFavoriteProducts(clientID);
    }

    @Override
    public List<Pair<String, Integer>> getTopNClients(int n) {
        return this.gestVendas.getTopNClients(n);
    }

    public List<Pair<String, Integer>> getTopNProducts(int n) {
        return this.gestVendas.getTopNProducts(n);
    }
}
