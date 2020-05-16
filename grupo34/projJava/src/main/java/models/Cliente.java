package models;

import java.util.*;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

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

    public List<String> getFavoriteProducts() {
        Map<String, Integer> produtos_por_quantidade = getProdutosPorQuantidade();
        return produtos_por_quantidade.entrySet().stream()
                .sorted((p1, p2) -> {
                    if(p1.getValue().equals(p2.getValue())) {
                        return p1.getKey().compareTo(p2.getKey());
                    }
                    return p2.getValue() - p1.getValue();
                })
                .map(Map.Entry::getKey)
                .collect(Collectors.toList());
    }

    public Map<String, Integer> getProdutosPorQuantidade() {
        Map<String, Integer> produtos_por_quantidade = new HashMap<>();
        this.compras_por_mes.forEach(mes -> {
            mes.forEach(venda -> {
                int atual = produtos_por_quantidade.getOrDefault(venda.getProductID(), 0);
                int novo = atual + venda.getUnidades();
                produtos_por_quantidade.put(venda.getProductID(), novo);
            });
        });
        return produtos_por_quantidade;
    }

    public int getDistinctProducts() {
        int total = 0;
        for (List<Venda> vendas_mes : this.compras_por_mes) {
            total += vendas_mes.stream().map(Venda::getProductID).distinct().count();
        }
        return total;
    }
}
