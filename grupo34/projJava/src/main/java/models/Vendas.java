package models;

import java.io.InvalidClassException;
import java.util.*;
import java.util.stream.Collectors;

public class Vendas {
    private final List<Set<Venda>> vendas_por_mes;


    public Vendas() {
        this.vendas_por_mes = new ArrayList<>(12);
        for (int mes = 0; mes < 12; mes++) {
            this.vendas_por_mes.add(new HashSet<>());
        }
    }

    public Optional<Venda> addVenda(String venda_completa, GestVendas gestVendas) {
        try {
            Venda venda = new Venda(venda_completa, gestVendas);
            if(this.vendas_por_mes.get(venda.getMes()).add(venda)) {
                return Optional.of(venda);
            }
        } catch (InvalidClassException ignored) {}
        return Optional.empty();
    }

    public int getTotalVendas(int mes) {
        return this.vendas_por_mes.get(mes).size();
    }

    public Double getTotalFaturacaoMesFilial(int mes, int filial){
        return this.vendas_por_mes.get(mes)
                .stream()
                .filter(venda -> venda.getFilial() == filial)
                .mapToDouble(Venda::getFaturacao)
                .sum();
    }
}
