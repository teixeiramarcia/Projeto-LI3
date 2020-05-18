package models;

import utils.Pair;

import java.util.List;
import java.util.Map;

public interface IGestVendas {
    void adicionaCliente(String clientID);

    void adicionaProduto(String productID);

    void adicionaVenda(String venda_completa);

    boolean existeProduto(String piece);

    boolean existeCliente(String piece);

    int getTotalComprasMes(int mes);

    Map<Integer, Double> getTotalFaturacaoMes(int mes);

    Map<Integer, Integer> getTotalClientesMes(int mes);

    List<String> getProdutosNComprados();

    int getNumClientesMes(int mes);

    List<Integer> getClientMonthlyBuyings(String clientID);

    List<Integer> getClientMonthlyProducts(String clientID);

    List<Double> getMonthlyTotalCost(String clientID);

    List<Integer> getProductMonthlyBuyings(String productID);

    List<Integer> getProductClients(String productID);

    List<Double> getProductBilling(String productID);

    boolean produtoExiste(String productID);

    List<String> getClientFavoriteProducts(String clientID);

    List<Pair<String, Integer>> getTopNClients(int n);

    List<Pair<String, Integer>> getTopNProducts(int n);
}
