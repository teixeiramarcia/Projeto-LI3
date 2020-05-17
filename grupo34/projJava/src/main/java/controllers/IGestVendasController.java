package controllers;

import utils.Pair;

import java.io.FileNotFoundException;
import java.util.List;
import java.util.Map;

public interface IGestVendasController {
    void loadSGVFromFiles(String filesFolderPath) throws FileNotFoundException;

    Map<String, Integer> getTotalCompras();

    Map<String, Map<Integer, Double>> getTotalFaturacao();

    Map<String, Map<Integer, Integer>> getTotalClientesMesFilial();

    List<String> getProdutosNuncaComprados();

    int getTotalVendas(int mes);

    int getTotalClientes(int mes);

    List<Integer> getClientMonthlyBuyings(String clientID);

    List<Integer> getClientMonthlyProducts(String clientID);

    List<Double> getMonthlyTotalCost(String clientID);

    List<Integer> getProductMonthlyBuyings(String productID);

    List<Integer> getProductClients(String productID);

    List<Double> getProductBilling(String productID);

    boolean clienteValido(String clientID);

    boolean clienteExiste(String clientID);

    boolean produtoValido(String productID);

    boolean produtoExiste(String productID);

    List<String> getClientFavoriteProducts(String clientID);

    List<Pair<String, Integer>> getTopNClients(int n);
}
