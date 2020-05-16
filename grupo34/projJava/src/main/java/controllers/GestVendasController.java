package controllers;

import models.Cliente;
import models.GestVendas;
import models.Produto;
import utils.Chrono;
import utils.Pair;
import views.Meses;

import java.io.*;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class GestVendasController {
    private GestVendas gestVendas;

    private void readClients(String file, GestVendas gestVendas) throws FileNotFoundException {
        BufferedReader bf = new BufferedReader(new FileReader(file));
        Iterator<String> it = bf.lines().iterator();
        while (it.hasNext()) {
            String line = it.next();
            gestVendas.adicionaCliente(line);
        }
    }

    private void readProducts(String file, GestVendas gestVendas) throws FileNotFoundException {
        BufferedReader bf = new BufferedReader(new FileReader(file));
        Iterator<String> it = bf.lines().iterator();
        while (it.hasNext()) {
            String line = it.next();
            gestVendas.adicionaProduto(line);
        }
    }

    private void readVendas(String file, GestVendas gestVendas) throws FileNotFoundException {
        BufferedReader bf = new BufferedReader(new FileReader(file));
        Iterator<String> it = bf.lines().iterator();
        while (it.hasNext()) {
            String line = it.next();
            gestVendas.adicionaVenda(line);
        }
    }

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

    public Map<String, Integer> getTotalCompras() {
        Map<String, Integer> resultado = new HashMap<>();
        for(int mes=0; mes < 12; mes++) {
            resultado.put(Meses.intToMes(mes), this.gestVendas.getTotalComprasMes(mes));
        }
        return resultado;
    }

    public Map<String, Map<Integer, Double>> getTotalFaturacao() {
        Map<String, Map<Integer, Double>> resultado = new HashMap<>();
        for (int mes = 0; mes < 12; mes++)
            resultado.put(Meses.intToMes(mes), this.gestVendas.getTotalFaturacaoMes(mes));
        return resultado;
    }

    public Map<String, Map<Integer, Integer>> getTotalClientesMesFilial() {
        Map<String, Map<Integer, Integer>> resultado = new HashMap<>();
        for (int mes = 0; mes < 12; mes++)
            resultado.put(Meses.intToMes(mes), this.gestVendas.getTotalClientesMes(mes));
        return resultado;
    }

    public List<String> getProdutosNuncaComprados() {
        return this.gestVendas.getProdutosNComprados();
    }

    public int getTotalVendas(int mes) {
        return this.gestVendas.getTotalComprasMes(mes);
    }

    public int getTotalClientes(int mes) {
        return this.gestVendas.getNumClientesMes(mes);
    }

    public List<Integer> getClientMonthlyBuyings(String clientID) {
        return this.gestVendas.getClientMonthlyBuyings(clientID);
    }

    public List<Integer> getClientMonthlyProducts(String clientID) {
        return this.gestVendas.getClientMonthlyProducts(clientID);
    }

    public List<Double> getMonthlyTotalCost(String clientID) {
        return this.gestVendas.getMonthlyTotalCost(clientID);
    }

    public List<Integer> getProductMonthlyBuyings(String productID) {
        return this.gestVendas.getProductMonthlyBuyings(productID);
    }

    public List<Integer> getProductClients(String productID) {
        return this.gestVendas.getProductClients(productID);
    }

    public List<Double> getProductBilling(String productID) {
        return this.gestVendas.getProductBilling(productID);
    }

    public boolean clienteValido(String clientID) {
        return Cliente.validaCliente(clientID);
    }

    public boolean clienteExiste(String clientID) {
        return this.gestVendas.existeCliente(clientID);
    }

    public boolean produtoValido(String productID) {
        return Produto.validaProduto(productID);
    }

    public boolean produtoExiste(String productID) {
        return this.gestVendas.produtoExiste(productID);
    }

    public List<String> getClientFavoriteProducts(String clientID) {
        return this.gestVendas.getClientFavoriteProducts(clientID);
    }

    public List<Pair<String, Integer>> getTopNClients(int n) {
        return this.gestVendas.getTopNClients(n);
    }
}
