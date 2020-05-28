package models;

import java.util.List;
import java.util.Map;
import java.util.regex.Pattern;

public interface ICliente {
    Pattern pattern = Pattern.compile("[A-Z]([1-4]\\d{3}|5000)");

    /**
     * Método que efetua a validação do código de um cliente
     *
     * @param line código do cliente em causa
     * @return true se o código for válido, false caso contrário
     */
    static boolean validaCliente(String line) {
        return ICliente.pattern.matcher(line.trim()).matches();
    }

    /**
     * Getter para o código do cliente
     *
     * @return código do cliente
     */
    String getClientID();

    /**
     * Getter para a faturação numa determinada filial
     *
     * @param filial filial escolhida
     * @return faturação total de uma determinada filial
     */
    double getFaturacaoFilial(int filial);

    /**
     * Método que atualiza as informações de um cliente com as de uma nova venda.
     *
     * @param IVenda venda com informação para atualizar o cliente
     */
    void updateCliente(IVenda IVenda);

    /**
     * Método que verifica se o cliente comprou num determinado mês e numa determinada filial
     *
     * @param mes    mês a ser consultado
     * @param filial filial a ser consultada
     * @return true se o cliente comprou naquele mês e naquela filial, false caso contrário
     */
    boolean comprouNoMesEFilial(int mes, int filial);

    /**
     * Método que verifica se o cliente comprou num determinado mês
     *
     * @param mes mês a ser consultado
     * @return true se o cliente comprou no mês, false caso contrário
     */
    boolean comprouNoMes(int mes);

    /**
     * Método que devolve a listagem de compras mensais do cliente
     *
     * @return listagem das compras do cliente separadas por mês
     */
    List<Integer> getMonthlyBuyings();

    /**
     * Método que devolve a quantidade de produtos distintos que o cliente comprou por mês
     *
     * @return quantidade de produtos distintos comprados pelo cliente mensalmente
     */
    List<Integer> getMonthlyProducts();

    /**
     * Método que devolve os gastos por mês do cliente
     *
     * @return listagem dos gastos mensais do cliente
     */
    List<Double> getMonthlyTotalCost();

    /**
     * Método que devolve a listagem dos produtos favoritos do cliente ordenados por vezes comprado
     *
     * @return lista ordenada dos códigos dos produtos favoritos do cliente
     */
    List<String> getFavoriteProducts();

    /**
     * Método que devolve um mapa com todos os códigos de produtos comprados pelo cliente e respetiva quantidade comprada
     *
     * @return produtos comprados e respetiva quantidade
     */
    Map<String, Integer> getProdutosPorQuantidade();

    /**
     * Método que devolve a quantidade de produtos distintos comprados pelo cliente
     *
     * @return contagem de produtos distintos comprados pelo cliente
     */
    int getDistinctProducts();
}
