package models;

import utils.Pair;

import java.util.List;

public interface IProdutos {
    /**
     * Método que verifica se um produto existe
     *
     * @param productID produto em questão
     * @return true se o produto existir, false caso contrário
     */
    boolean existeProduto(String productID);

    /**
     * Método que adiciona um produto novo à estrutura de dados
     *
     * @param IProduto produto a ser adicionado
     */
    void addProduct(IProduto IProduto);

    /**
     * Método que atualiza os produtos com uma nova venda
     *
     * @param IVenda venda a ter em conta na atualização
     */
    void updateProdutos(IVenda IVenda);

    /**
     * Método que devolve uma listagem de todos os produtos que nunca foram comprados
     *
     * @return lista de produtos nunca comprados
     */
    List<String> getProductsNeverBought();

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
     * Método que devolve os top n produtos (mais comprados) do sistema
     *
     * @param n número máximo de produtos listados
     * @return top n produtos
     */
    List<Pair<String, Integer>> getTopNProducts(int n);

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
