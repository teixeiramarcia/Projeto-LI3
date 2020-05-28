package models;

import utils.Pair;

import java.util.List;
import java.util.regex.Pattern;

public interface IProduto {
    Pattern pattern = Pattern.compile("[A-Z]{2}[1-9]\\d{3}");

    /**
     * Método que verifica se um código de produto é válido
     *
     * @param line código do produto em questão
     * @return true se for válido, false caso contrário
     */
    static boolean validaProduto(String line) {
        String pieces = line.trim();
        return IProduto.pattern.matcher(pieces).matches();
    }

    /**
     * Getter do código do produto
     *
     * @return código do produto
     */
    String getProductID();

    /**
     * Método que atualiza o produto com uma nova venda
     *
     * @param IVenda venda a ter em conta na atualização
     */
    void updateProduto(IVenda IVenda);

    /**
     * Método que verifica se um produto nunca foi comprado
     *
     * @return true se nunca tiver sido comprado, false caso contrário
     */
    boolean wasntBoughtGeneral();

    /**
     * Método que devolve as compras mensais do produto
     *
     * @return listagem mensal das compras do produto
     */
    List<Integer> getMonthlyBuyings();

    /**
     * Método que devolve a listagem de clientes que compraram o produto
     *
     * @return listagem de clientes que compraram o produto
     */
    List<Integer> getClients();

    /**
     * Método que devolve a faturação do produto mensalmente
     *
     * @return listagem mensal da faturação do produto
     */
    List<Double> getTotalBilling();

    /**
     * Método que devolve a contagem de clientes que compraram o produto
     *
     * @return total de clientes que compraram o produto
     */
    int getDistinctClients();

    /**
     * Método que devolve os top n clientes que mais gastaram no produto
     *
     * @param n limite máximo de clientes apresentados
     * @return top n clientes do produto
     */
    List<Pair<String, Double>> getTopNClients(int n);

    /**
     * Método que devolve a faturação do produto por mês e por filial
     *
     * @return par de produto-faturação por mês e filial
     */
    Pair<String, List<Double>> getFaturacaoMesFilial();
}
