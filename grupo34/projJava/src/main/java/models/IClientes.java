package models;

import utils.Pair;

import java.util.List;

public interface IClientes {
    /**
     * Método que devolve o cliente que efetuou uma determinada venda
     *
     * @param IVenda compra efetuada
     * @return cliente que efetuou a compra
     */
    ICliente getClient(IVenda IVenda);

    /**
     * Método que verifica se um cliente existe
     *
     * @param clientID cliente em questão
     * @return true se o cliente existir, false caso contrário
     */
    boolean existeCliente(String clientID);

    /**
     * Método que guarda um cliente no sistema
     *
     * @param ICliente cliente a ser guardado
     */
    void addClient(ICliente ICliente);

    /**
     * Método que atualiza a informação de os clientes com uma nova venda
     *
     * @param IVenda venda a ser considerada para efeitos de atualização
     */
    void updateClientes(IVenda IVenda);

    /**
     * Método que devolve o total de clientes que efetuaram compras num determinado mês
     *
     * @param mes mês em questão
     * @return contagem de clientes que compraram no mês
     */
    int getTotalClientesMes(int mes);

    /**
     * Método que devolve o total de clientes que efetuaram compras numa determinada filial e num determinado mês
     *
     * @param filial filial em questão
     * @param mes    mês em questão
     * @return contagem de clientes numa filial e num mês
     */
    int getTotalClientesFilialMes(int filial, int mes);

    /**
     * Método que devolve as compras mensais de um determinado cliente
     *
     * @param clientID cliente em questão
     * @return listagem das compras mensais do cliente
     */
    List<Integer> getClientMonthlyBuyings(String clientID);

    /**
     * Método que devolve o total de produtos comprados por um determinado cliente por mês
     *
     * @param clientID cliente em questão
     * @return listagem mensal do total de produtos comprados por um cliente
     */
    List<Integer> getClientMonthlyProducts(String clientID);

    /**
     * Método que devolve os gastos mensais de um determinado cliente
     *
     * @param clientID cliente em questão
     * @return listagem mensal dos gastos de um cliente
     */
    List<Double> getMonthlyTotalCost(String clientID);

    /**
     * Método que devolve os produtos favoritos de um determinado cliente
     *
     * @param clientID cliente em questão
     * @return listagem ordenada dos produtos favoritos de um cliente
     */
    List<String> getClientFavoriteProducts(String clientID);

    /**
     * Método que devolve os top n clientes do sistema (por faturação)
     *
     * @param n limite máximo de clientes a apresentar
     * @return top n clientes
     */
    List<Pair<String, Integer>> getTopNClients(int n);
}
