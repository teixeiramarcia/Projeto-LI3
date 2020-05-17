package models;

import utils.Pair;

import java.util.List;

public interface IClientes {
    ICliente getClient(IVenda IVenda);

    boolean existeCliente(String clientID);

    void addClient(ICliente ICliente);

    void updateClientes(IVenda IVenda);

    int getTotalClientesFilialMes(int filial, int mes);

    List<Integer> getClientMonthlyBuyings(String clientID);

    List<Integer> getClientMonthlyProducts(String clientID);

    List<Double> getMonthlyTotalCost(String clientID);

    List<String> getClientFavoriteProducts(String clientID);

    List<Pair<String, Integer>> getTopNClients(int n);
}
