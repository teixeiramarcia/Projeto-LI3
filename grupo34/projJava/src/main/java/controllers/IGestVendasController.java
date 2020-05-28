package controllers;

import utils.Pair;

import java.io.FileNotFoundException;
import java.util.List;
import java.util.Map;

public interface IGestVendasController {
    /**
     * Método que carrega os ficheiros de dados para as estruturas em memória.
     *
     * @param filesFolderPath caminho para os ficheiros de dados
     * @param sales_file      escolha feita pelo utilizador acerca do ficheiro de vendas a carregar (ou .dat)
     * @throws FileNotFoundException é lançada a expceção se os ficheiros de dados não existirem
     */
    void loadSGVFromFiles(String filesFolderPath, String sales_file) throws FileNotFoundException;

    /**
     * Método que guarda o estado do programa num ficheiro .dat
     *
     * @param filesFolderPath caminho para os ficheiros de dados onde ficará o ficheiro .dat
     */
    void saveProgramStatus(String filesFolderPath);

    /**
     * Método que devolve o nome do último ficheiro de vendas carregado para memória central
     *
     * @return nome do ficheiro de vendas
     */
    String getLastSalesFileName();

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
     * Método que devolve o total de compras efetuadas por mês na forma de um mapa
     *
     * @return total de compras mensais
     */
    Map<String, Integer> getTotalCompras();

    /**
     * Método que devolve sob a forma de um mapa de mapas (tabela) a faturação total por mês e por filial
     *
     * @return faturação total por mês e por filial
     */
    Map<String, Map<Integer, Double>> getTotalFaturacao();

    /**
     * Método que devolve o número de clientes que efetuaram compras por filial e por mês
     *
     * @return contagem de clientes que efetuaram compras por mês e por filial
     */
    Map<String, Map<Integer, Integer>> getNumClientesCompraramFilialPorMes();

    /**
     * Método que devolve uma lista dos produtos que nunca foram comprados
     *
     * @return listagem de produtos nunca comprados
     */
    List<String> getProdutosNuncaComprados();

    /**
     * Método que devolve o total de vendas efetuadas num determinado mês
     *
     * @param mes mês em que foram efetuadas as vendas
     * @return contagem de vendas no mês indicado
     */
    int getTotalVendas(int mes);

    /**
     * Método que devolve o total de clientes que compraram num determinado mês
     *
     * @param mes mês selecionado
     * @return contagem de clientes que compraram no mês indicado
     */
    int getNumClientesCompraramNoMes(int mes);

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
     * Método que verifica se um cliente é válido
     *
     * @param clientID cliente em questão
     * @return true se o cliente for válido, false caso contrário
     */
    boolean clienteValido(String clientID);

    /**
     * Método que verifica se um cliente existe
     *
     * @param clientID cliente em questão
     * @return true se o cliente existir, false caso contrário
     */
    boolean clienteExiste(String clientID);

    /**
     * Método que verifica se um produto é válido
     *
     * @param productID produto em questão
     * @return true se o produto for válido, false caso contrário
     */
    boolean produtoValido(String productID);

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
