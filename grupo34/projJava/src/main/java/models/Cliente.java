package models;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Cliente implements ICliente {
    private final String clientID;
    private final int[] faturacao_filial;
    private final List<List<IVenda>> compras_por_mes;

    public Cliente(String clientID) {
        this.clientID = clientID;
        this.faturacao_filial = new int[3];
        this.compras_por_mes = new ArrayList<>(3);
        for (int mes = 0; mes < 12; mes++) {
            this.compras_por_mes.add(new ArrayList<>());
        }
    }

    @Override
    public String getClientID() {
        return this.clientID;
    }

    @Override
    public int getFaturacaoFilial(int filial) {
        return this.faturacao_filial[filial];
    }

    @Override
    public void updateCliente(IVenda IVenda) {
        this.compras_por_mes.get(IVenda.getMes()).add(IVenda);
        this.faturacao_filial[IVenda.getFilial()] += IVenda.getFaturacao();
    }

    @Override
    public boolean comprouNoMesEFilial(int mes, int filial){
        return compras_por_mes.get(mes).stream().anyMatch(compra -> compra.getFilial() == filial);
    }

    @Override
    public boolean comprouNoMes(int mes) {
        return this.compras_por_mes.get(mes).size() != 0;
    }

    @Override
    public List<Integer> getMonthlyBuyings() {
        List<Integer> resultado = new ArrayList<>();
        for (int mes = 0; mes < 12; mes++) {
            resultado.add(mes, this.compras_por_mes.get(mes).size());
        }
        return resultado;
    }

    @Override
    public List<Integer> getMonthlyProducts() {
        List<Integer> resultado = new ArrayList<>();
        this.compras_por_mes.forEach(compras_mes -> resultado.add((int) compras_mes
                .stream()
                .map(IVenda::getProductID)
                .distinct()
                .count()));
        return resultado;
    }

    @Override
    public List<Double> getMonthlyTotalCost() {
        List<Double> resultado = new ArrayList<>();
        this.compras_por_mes.forEach(compras_mes -> resultado.add(compras_mes
                .stream()
                .mapToDouble(IVenda::getFaturacao)
                .sum()));
        return resultado;
    }

    @Override
    public List<String> getFavoriteProducts() {
        Map<String, Integer> produtos_por_quantidade = getProdutosPorQuantidade();
        return produtos_por_quantidade.entrySet().stream()
                .sorted((p1, p2) -> {
                    if (p1.getValue().equals(p2.getValue())) {
                        return p1.getKey().compareTo(p2.getKey());
                    }
                    return p2.getValue() - p1.getValue();
                })
                .map(Map.Entry::getKey)
                .collect(Collectors.toList());
    }

    @Override
    public Map<String, Integer> getProdutosPorQuantidade() {
        Map<String, Integer> produtos_por_quantidade = new HashMap<>();
        this.compras_por_mes.forEach(mes ->
            mes.forEach(venda -> {
                int atual = produtos_por_quantidade.getOrDefault(venda.getProductID(), 0);
                int novo = atual + venda.getUnidades();
                produtos_por_quantidade.put(venda.getProductID(), novo);
            })
        );
        return produtos_por_quantidade;
    }

    @Override
    public int getDistinctProducts() {
        int total = 0;
        for (List<IVenda> vendas_mes : this.compras_por_mes) {
            total += vendas_mes.stream().map(IVenda::getProductID).distinct().count();
        }
        return total;
    }
}
