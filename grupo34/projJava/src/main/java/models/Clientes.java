package models;

import utils.Pair;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * {@inheritDoc}
 */

public class Clientes extends Model implements IClientes {
    private final Map<String, ICliente> clientes;

    public Clientes() {
        this.clientes = new HashMap<>();
    }

    @Override
    public ICliente getClient(IVenda IVenda) {
        return this.clientes.get(IVenda.getClientID());
    }

    @Override
    public boolean existeCliente(String clientID) {
        return this.clientes.containsKey(clientID);
    }

    @Override
    public void addClient(ICliente ICliente) {
        this.clientes.put(ICliente.getClientID(), ICliente);
    }

    @Override
    public void updateClientes(IVenda IVenda) {
        this.clientes.get(IVenda.getClientID()).updateCliente(IVenda);
    }

    @Override
    public int getTotalClientesMes(int mes) {
        int resultado = 0;
        for (ICliente cliente : clientes.values()) {
            if (cliente.comprouNoMes(mes)) {
                resultado++;
            }
        }
        return resultado;
    }

    @Override
    public int getTotalClientesFilialMes(int filial, int mes) {
        int resultado = 0;
        for (ICliente cliente : this.clientes.values()) {
            if (cliente.comprouNoMesEFilial(mes, filial)) {
                resultado++;
            }
        }
        return resultado;
    }

    @Override
    public List<Integer> getClientMonthlyBuyings(String clientID) {
        return this.clientes.get(clientID).getMonthlyBuyings();
    }

    @Override
    public List<Integer> getClientMonthlyProducts(String clientID) {
        return this.clientes.get(clientID).getMonthlyProducts();
    }

    @Override
    public List<Double> getMonthlyTotalCost(String clientID) {
        return this.clientes.get(clientID).getMonthlyTotalCost();
    }

    @Override
    public List<String> getClientFavoriteProducts(String clientID) {
        return this.clientes.get(clientID).getFavoriteProducts();
    }

    @Override
    public List<Pair<String, Integer>> getTopNClients(int n) {
        Stream<Pair<String, Integer>> s = this.clientes.values().stream()
                .map(cliente -> Pair.of(cliente.getClientID(), cliente.getDistinctProducts()));
        return s.sorted((par1, par2) -> par2.getSecond() - par1.getSecond())
                .limit(n)
                .collect(Collectors.toList());
    }
}
