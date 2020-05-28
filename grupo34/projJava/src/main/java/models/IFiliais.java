package models;

public interface IFiliais {
    /**
     * Método que atualiza a informação das filiais com uma nova venda feita a um cliente
     *
     * @param IVenda   venda para atualização de dados
     * @param ICliente cliente que efetuou a compra
     */
    void updateFiliais(IVenda IVenda, ICliente ICliente);

    /**
     * Método que devolve os top 3 clientes de cada filial
     *
     * @return top 3 clientes de cada filial
     */
    String[][] getTop3Buyers();
}
