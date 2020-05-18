package models;

import java.util.*;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class Produto implements IProduto {
    private final String productID;
    private final int[] vezes_comprado = new int[12];
    private final List<Set<String>> clientes_que_compraram;
    private final double[] faturacao = new double[12];

    public Produto(String productID) {
        this.productID = productID;
        this.clientes_que_compraram = new ArrayList<>(12);
        for (int mes = 0; mes < 12; mes++) {
            this.clientes_que_compraram.add(mes, new HashSet<>());
        }
    }

    @Override
    public String getProductID() {
        return productID;
    }

    @Override
    public void updateProduto(IVenda IVenda) {
        this.vezes_comprado[IVenda.getMes()] += IVenda.getUnidades();
        this.clientes_que_compraram.get(IVenda.getMes()).add(IVenda.getClientID());
        this.faturacao[IVenda.getMes()] += IVenda.getFaturacao();
    }

    @Override
    public boolean wasntBoughtGeneral() {
        for (int mes = 0; mes < 12; mes++) {
            if (this.vezes_comprado[mes] != 0) return false;
        }
        return true;
    }

    @Override
    public List<Integer> getMonthlyBuyings() {
        List<Integer> resultado = new ArrayList<>();
        for (int mes = 0; mes < 12; mes++) {
            resultado.add(mes, this.vezes_comprado[mes]);
        }
        return resultado;
    }

    @Override
    public List<Integer> getClients() {
        List<Integer> resultado = new ArrayList<>();
        for (int mes = 0; mes < 12; mes++) {
            resultado.add(mes, this.clientes_que_compraram.get(mes).size());
        }
        return resultado;
    }

    @Override
    public List<Double> getTotalBilling() {
        List<Double> resultado = new ArrayList<>();
        for (int mes = 0; mes < 12; mes++) {
            resultado.add(mes, this.faturacao[mes]);
        }
        return resultado;
    }

    public int getDistinctClients() {
        Set<String> clientes = new TreeSet<>();
        this.clientes_que_compraram.forEach(clientes::addAll);
        return clientes.size();
    }
}
