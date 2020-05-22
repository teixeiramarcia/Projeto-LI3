package models;

import java.io.InvalidClassException;
import java.util.*;

public class Vendas implements IVendas {
    private final List<List<IVenda>> vendas_por_mes;


    public Vendas() {
        this.vendas_por_mes = new ArrayList<>(12);
        for (int mes = 0; mes < 12; mes++) {
            this.vendas_por_mes.add(new ArrayList<>());
        }
    }

    @Override
    public Optional<IVenda> addVenda(String venda_completa, IGestVendas IGestVendas) {
        IVenda venda;

        try {
            venda = new Venda(venda_completa, IGestVendas);
        } catch (InvalidClassException e) {
            return Optional.empty();
        }

        this.vendas_por_mes.get(venda.getMes()).add(venda);
        return Optional.of(venda);
    }

    @Override
    public int getTotalVendas(int mes) {
        return this.vendas_por_mes.get(mes).size();
    }

    @Override
    public Double getTotalFaturacaoMesFilial(int mes, int filial) {
        return this.vendas_por_mes.get(mes)
                .stream()
                .filter(venda -> venda.getFilial() == filial)
                .mapToDouble(IVenda::getFaturacao)
                .sum();
    }

    @Override
    public int getDistinctProducts() {
        Set<String> produtos = new TreeSet<>();
        this.vendas_por_mes.forEach(vendas_mes -> {
            vendas_mes.forEach(venda -> produtos.add(venda.getProductID()));
        });
        return produtos.size();
    }

    @Override
    public int getTotalBuyingClients() {
        Set<String> clientes = new TreeSet<>();
        this.vendas_por_mes.forEach(vendas_mes -> {
            vendas_mes.forEach(venda -> clientes.add(venda.getClientID()));
        });
        return clientes.size();
    }

    @Override
    public int getZeroSales() {
        List<IVenda> vendas = new ArrayList<>();
        this.vendas_por_mes.forEach(vendas::addAll);
        return (int) vendas.stream().filter(venda -> venda.getFaturacao() == 0).count();
    }

    @Override
    public double getTotalBilling() {
        List<IVenda> vendas = new ArrayList<>();
        this.vendas_por_mes.forEach(vendas::addAll);
        return vendas.stream().mapToDouble(IVenda::getFaturacao).sum();
    }
}
