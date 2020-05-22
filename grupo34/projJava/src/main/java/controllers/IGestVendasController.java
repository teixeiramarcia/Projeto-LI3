package controllers;

import utils.Pair;

import java.io.FileNotFoundException;
import java.util.List;
import java.util.Map;

public interface IGestVendasController {
    void loadSGVFromFiles(String filesFolderPath) throws FileNotFoundException;

    String getLastSalesFileName();

    int getWrongSales();

    int getTotalProducts();

    int getTotalDistinctBoughtProducts();

    int getTotalNeverBoughtProducts();

    int getTotalClients();

    int getTotalBuyingClients();

    int getNeverBuyingClients();

    int getZeroSales();

    double getTotalBilling();

    Map<String, Integer> getTotalCompras();

    Map<String, Map<Integer, Double>> getTotalFaturacao();

    Map<String, Map<Integer, Integer>> getNumClientesCompraramFilialPorMes();

    List<String> getProdutosNuncaComprados();

    int getTotalVendas(int mes);

    int getNumClientesCompraramNoMes(int mes);

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

    List<Pair<String, Integer>> getTopNProducts(int n);

    String[][] getTop3Buyers();

    List<Pair<String, Double>> getTopNClientsOfProduct(String productID, int n);
}
