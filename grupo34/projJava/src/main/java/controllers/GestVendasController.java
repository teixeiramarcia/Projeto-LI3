package controllers;

import models.GestVendas;
import models.ICliente;
import models.IGestVendas;
import models.IProduto;
import utils.Chrono;
import utils.Pair;
import views.Meses;

import java.io.*;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

/**
 * {@inheritDoc}
 */
public class GestVendasController implements IGestVendasController {
    private IGestVendas gestVendas;
    private String lastVendasFileName;

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

    private void readFromDatFile(String filesFolderPath) throws FileNotFoundException {
        File tempFile = new File(filesFolderPath + "/gestVendas.dat");
        if (!tempFile.exists()) {
            throw new FileNotFoundException();
        }

        try (
                FileInputStream is = new FileInputStream(tempFile);
                ObjectInputStream ois = new ObjectInputStream(is)
        ) {
            this.gestVendas = (GestVendas) ois.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    private void readFromFiles(String filesFolderPath, String sales_file) throws FileNotFoundException {
        String ficheiro_clientes = filesFolderPath + "/Clientes.txt";
        readClients(ficheiro_clientes, gestVendas);

        String ficheiro_produtos = filesFolderPath + "/Produtos.txt";
        readProducts(ficheiro_produtos, gestVendas);

        String ficheiro_vendas = filesFolderPath + "/" + sales_file;
        this.lastVendasFileName = ficheiro_vendas;
        readVendas(ficheiro_vendas, gestVendas);
    }

    @Override
    public void loadSGVFromFiles(String filesFolderPath, String sales_file) throws FileNotFoundException {
        this.gestVendas = new GestVendas();
        Chrono.start();
        if (sales_file.equals("dat")) {
            readFromDatFile(filesFolderPath);
        } else {
            readFromFiles(filesFolderPath, sales_file);
        }
        Chrono.stop();
        System.out.println(Chrono.getTimeString());
    }

    @Override
    public void saveProgramStatus(String filesFolderPath) {
        try (
                FileOutputStream fos = new FileOutputStream(filesFolderPath + "/gestVendas.dat");
                ObjectOutputStream oos = new ObjectOutputStream(fos)
        ) {
            oos.writeObject(this.gestVendas);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public String getLastSalesFileName() {
        return this.lastVendasFileName;
    }

    @Override
    public int getWrongSales() {
        return this.gestVendas.getWrongSales();
    }

    @Override
    public int getTotalProducts() {
        return this.gestVendas.getTotalProducts();
    }

    @Override
    public int getTotalDistinctBoughtProducts() {
        return this.gestVendas.getTotalDistinctBoughtProducts();
    }

    @Override
    public int getTotalNeverBoughtProducts() {
        return this.gestVendas.getTotalNeverBoughtProducts();
    }

    @Override
    public int getTotalClients() {
        return this.gestVendas.getTotalClients();
    }

    @Override
    public int getTotalBuyingClients() {
        return this.gestVendas.getTotalBuyingClients();
    }

    @Override
    public int getNeverBuyingClients() {
        return this.gestVendas.getNeverBuyingClients();
    }

    @Override
    public int getZeroSales() {
        return this.gestVendas.getZeroSales();
    }

    @Override
    public double getTotalBilling() {
        return this.gestVendas.getTotalBilling();
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
    public Map<String, Map<Integer, Integer>> getNumClientesCompraramFilialPorMes() {
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
    public int getNumClientesCompraramNoMes(int mes) {
        return this.gestVendas.getNumClientesCompraramNoMes(mes);
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

    @Override
    public String[][] getTop3Buyers() {
        return this.gestVendas.getTop3Buyers();
    }

    @Override
    public List<Pair<String, Double>> getTopNClientsOfProduct(String productID, int n) {
        return this.gestVendas.getTopNClientsOfProduct(productID, n);
    }

    @Override
    public List<Pair<String, List<Double>>> getFaturacaoPorProduto() {
        return this.gestVendas.getFaturacaoPorProduto();
    }
}
