package models;

import utils.Pair;

import java.util.List;
import java.util.Map;

public interface IGestVendas {
    /**
     * Método que adiciona um cliente ao sistema
     *
     * @param clientID identificador do cliente a ser adicionado
     */
    void adicionaCliente(String clientID);

    /**
     * Método que adiciona um produto ao sistema
     *
     * @param productID identificador do produto a ser adicionado
     */
    void adicionaProduto(String productID);

    /**
     * Método que adiciona uma venda ao sistema
     *
     * @param venda_completa venda a ser adicionada
     */
    void adicionaVenda(String venda_completa);

    /**
     * Método que verifica se um produto já existe
     *
     * @param piece identificador do produto
     * @return true se o produto já existir, false caso contrário
     */
    boolean existeProduto(String piece);

    /**
     * Método que verifica se um cliente já existe
     *
     * @param piece identificador do cliente
     * @return true se o cliente já existir, false caso contrário
     */
    boolean existeCliente(String piece);

    /**
     * Método que devolve o número de vendas erradas
     *
     * @return contagem de vendas erradas
     */
    int getWrongSales();

    /**
     * Método que devolve o número total de produtos
     *
     * @return contagem total de produtos
     */
    int getTotalProducts();

    /**
     * Método que devolve o total de produtos distintos comprados
     *
     * @return contagem de produtos distintos comprados
     */
    int getTotalDistinctBoughtProducts();

    /**
     * Método que devolve o total de produtos que nunca foram comprados
     *
     * @return contagem de produtos nunca comprados
     */
    int getTotalNeverBoughtProducts();

    /**
     * Método que devolve o total de clientes existentes
     *
     * @return contagem total de clientes
     */
    int getTotalClients();

    /**
     * Método que devolve o total de clientes que efetuaram compras
     *
     * @return contagem de clientes que efetuaram compras
     */
    int getTotalBuyingClients();

    /**
     * Método que devolve o total de clientes que nunca efeuaram compras
     *
     * @return contagem de clientes que nunca efetuaram compras
     */
    int getNeverBuyingClients();

    /**
     * Método que devolve o número de vendas que têm valor total zero
     *
     * @return contagem de vendas cujo valor total é zero
     */
    int getZeroSales();

    /**
     * Método que devolve a faturação total
     *
     * @return faturação total
     */
    double getTotalBilling();

    /**
     * Método que devolve o total de clientes que compraram num determinado mês
     *
     * @param mes mês selecionado
     * @return contagem de clientes que compraram no mês indicado
     */
    int getNumClientesCompraramNoMes(int mes);

    /**
     * Método que devolve o total de compras num determinado mês
     *
     * @param mes mês selecionado
     * @return contagem de compras no mês
     */
    int getTotalComprasMes(int mes);

    /**
     * Método que devolve a faturação total de um determinado mês em todas as filiais
     *
     * @param mes mes selecionado
     * @return mapa de faturações num determinado mês em todas as filiais
     */
    Map<Integer, Double> getTotalFaturacaoMes(int mes);

    /**
     * Método que devolve o total de clientes que fizeram compras num determinado mês em todas as filiais
     *
     * @param mes mês selecionado
     * @return mapa de quantidades de clientes que compraram num determinado mês por filial
     */
    Map<Integer, Integer> getTotalClientesMes(int mes);

    /**
     * Método que devolve uma listagem de produtos nunca comprados
     *
     * @return produtos nunca comprados
     */
    List<String> getProdutosNComprados();

    /**
     * Método que devolve uma listagem do total de compras de um determinado cliente mensalmente
     *
     * @param clientID cliente em causa
     * @return listagem da contagem de compras mensais do cliente indicado
     */
    List<Integer> getClientMonthlyBuyings(String clientID);

    /**
     * Método que devolve uma listagem do total de produtos comprados por um determinado cliente mensalmente
     *
     * @param clientID cliente em causa
     * @return listagem da contagem de produtos comprados pelo cliente indicado mensalmente
     */
    List<Integer> getClientMonthlyProducts(String clientID);

    /**
     * Método que devolve os gastos totais de um cliente separados por mês
     *
     * @param clientID cliente em causa
     * @return listagem dos gastos mensais do cliente indicado
     */
    List<Double> getMonthlyTotalCost(String clientID);

    /**
     * Método que devolve as compras mensais de um determinado produto
     *
     * @param productID produto em questão
     * @return listagem mensal das compras de um determinado produto
     */
    List<Integer> getProductMonthlyBuyings(String productID);

    /**
     * Método que devolve a listagem de clientes que compraram um determinado produto
     *
     * @param productID produto em questão
     * @return listagem de clientes que compraram o produto em questão
     */
    List<Integer> getProductClients(String productID);

    /**
     * Método que devolve a faturação de um determinado produto mensalmente
     *
     * @param productID produto em questão
     * @return listagem mensal da faturação do produto em questão
     */
    List<Double> getProductBilling(String productID);

    /**
     * Método que verifica se um produto existe
     *
     * @param productID produto em questão
     * @return true se o produto existir, false caso contrário
     */
    boolean produtoExiste(String productID);

    /**
     * Método que devolve a listagem ordenada dos produtos favoritos de um determinado cliente
     *
     * @param clientID cliente em questão
     * @return listagem ordenada dos produtos favoritos de um cliente
     */
    List<String> getClientFavoriteProducts(String clientID);

    /**
     * Método que devolve os top n clientes do sistema (por faturação)
     *
     * @param n número máximo de clientes listados
     * @return top n clientes
     */
    List<Pair<String, Integer>> getTopNClients(int n);

    /**
     * Método que devolve os top n produtos (mais comprados) do sistema
     *
     * @param n número máximo de produtos listados
     * @return top n produtos
     */
    List<Pair<String, Integer>> getTopNProducts(int n);

    /**
     * Método que devolve os top 3 clientes do sistema (por produtos distintos comprados) por filial e por mês
     *
     * @return top n clientes
     */
    String[][] getTop3Buyers();

    /**
     * Método que devolve os top n clientes que mais gastaram num determinado produto
     *
     * @param productID produto em questão
     * @param n         limite máximo de clientes apresentados
     * @return top n clientes de um produto
     */
    List<Pair<String, Double>> getTopNClientsOfProduct(String productID, int n);

    /**
     * Método que devolve a listagem da faturação de cada produto existente no sistema
     *
     * @return listagem da faturação por produto por mês e por filial
     */
    List<Pair<String, List<Double>>> getFaturacaoPorProduto();
}
