package models;

import java.util.Optional;

public interface IVendas {
    /**
     * Método que adiciona uma nova venda à estrutura de dados
     *
     * @param venda_completa venda a ser adicionada
     * @param IGestVendas    sistema onde vai ser adicionada
     * @return devolve a venda ou null se não tiver sido adicionada com sucesso
     */
    Optional<IVenda> addVenda(String venda_completa, IGestVendas IGestVendas);

    /**
     * Método que devolve o total de vendas efetuadas num determinado mês
     *
     * @param mes mês a ser consultado
     * @return contagem da vendas efetuadas
     */
    int getTotalVendas(int mes);

    /**
     * Método que devolve a faturação total num determinado mês e numa determinada filial
     *
     * @param mes    mês a ser consultado
     * @param filial filial a ser consultada
     * @return faturação total num mês e numa filial
     */
    Double getTotalFaturacaoMesFilial(int mes, int filial);

    /**
     * Método que devolve o total de produtos distintos vendidos
     *
     * @return contagem de produtos distintos vendidos
     */
    int getDistinctProducts();

    /**
     * Método que devolve a contagem de clientes compradores
     *
     * @return total de compradores
     */
    int getTotalBuyingClients();

    /**
     * Método que devolve a quantidade de vendas com o valor zero
     *
     * @return total de vendas com o valor zero
     */
    int getZeroSales();

    /**
     * Método que devolve o total de faturação do sistema
     *
     * @return faturação total
     */
    double getTotalBilling();
}
