package models;

public interface IFilial {
    /**
     * Método que atualiza a informação da filial com uma nova venda feita a um cliente
     *
     * @param IVenda   venda para atualização de dados
     * @param ICliente cliente que efetuou a compra
     */
    void updateFilial(IVenda IVenda, ICliente ICliente);

    /**
     * Método que devolve os top 3 clientes da filial
     *
     * @return top 3 clientes da filial
     */
    String[] getTop3Buyers();
}
