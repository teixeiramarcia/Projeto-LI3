package models;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.regex.Pattern;

public class Cliente {
    private static final Pattern pattern = Pattern.compile("[A-Z]([1-4]\\d{3}|5000)");

    private final String clientID;
    private final int[] faturacao_filial;
    private final List<List<Venda>> compras_por_mes;

    public Cliente(String clientID) {
        this.clientID = clientID;
        this.faturacao_filial = new int[3];
        this.compras_por_mes = new ArrayList<>(3);
        for (int mes=0; mes < 12; mes++) {
            this.compras_por_mes.add(new ArrayList<>());
        }
    }

    public static boolean validaCliente(String line) {
        return pattern.matcher(line.trim()).matches();
    }

    public String getClientID() {
        return this.clientID;
    }

    public int getFaturacaoFilial(int filial) {
        return this.faturacao_filial[filial];
    }

    public void updateCliente(Venda venda) {
        this.compras_por_mes.get(venda.getMes()).add(venda);
        this.faturacao_filial[venda.getFilial()] += venda.getFaturacao();
    }

    public boolean faturouNaFilial(int filial) {
        return this.faturacao_filial[filial] != 0;
    }

    public boolean comprouNoMes(int mes) {
        return this.compras_por_mes.get(mes).size() != 0;
    }

    public List<Integer> getMonthlyBuyings() {
        List<Integer> resultado = new ArrayList<>();
        for (int mes = 0; mes < 12; mes++) {
            resultado.add(mes,this.compras_por_mes.get(mes).size());
        }
        return resultado;
    }

    public List<Integer> getMonthlyProducts() {
        List<Integer> resultado = new ArrayList<>();
        this.compras_por_mes.forEach(compras_mes -> resultado.add((int) compras_mes
                .stream()
                .map(Venda::getProductID)
                .distinct()
                .count()));
        return resultado;
    }

    public List<Double> getMonthlyTotalCost() {
        List<Double> resultado = new ArrayList<>();
        this.compras_por_mes.forEach(compras_mes -> resultado.add(compras_mes
                .stream()
                .mapToDouble(Venda::getFaturacao)
                .sum()));
        return resultado;
    }
}
