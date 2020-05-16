package models;

import utils.Pair;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Clientes {
    private final Map<String, Cliente> clientes;

    public Clientes() {
        this.clientes = new HashMap<>();
    }

    public Cliente getClient(Venda venda) {
        return this.clientes.get(venda.getClientID());
    }

    public boolean existeCliente(String clientID) {
        return this.clientes.containsKey(clientID);
    }

    public void addClient(Cliente cliente) {
        this.clientes.put(cliente.getClientID(), cliente);
    }

    public void updateClientes(Venda venda) {
        this.clientes.get(venda.getClientID()).updateCliente(venda);
    }

    public int getTotalClientesFilialMes(int filial, int mes) {
        int resultado = 0;
        for (Cliente cliente: clientes.values())
            if(cliente.faturouNaFilial(filial) && cliente.comprouNoMes(mes))
                resultado++;
        return resultado;
    }

    public List<Integer> getClientMonthlyBuyings(String clientID) {
        return this.clientes.get(clientID).getMonthlyBuyings();
    }

    public List<Integer> getClientMonthlyProducts(String clientID) {
        return this.clientes.get(clientID).getMonthlyProducts();
    }

    public List<Double> getMonthlyTotalCost(String clientID) {
        return this.clientes.get(clientID).getMonthlyTotalCost();
    }

    public List<String> getClientFavoriteProducts(String clientID) {
        return this.clientes.get(clientID).getFavoriteProducts();
    }

    public List<Pair<String, Integer>> getTopNClients(int n) {
        Stream<Pair<String, Integer>> s = this.clientes.values().stream()
                .map(cliente -> Pair.of(cliente.getClientID(), cliente.getDistinctProducts()));
        return s.sorted((par1, par2)-> par2.getSecond() - par1.getSecond())
                .limit(n)
                .collect(Collectors.toList());
    }
}
