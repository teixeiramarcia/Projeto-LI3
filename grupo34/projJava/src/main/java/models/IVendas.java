package models;

import java.util.Optional;

public interface IVendas {
    Optional<IVenda> addVenda(String venda_completa, IGestVendas IGestVendas);

    int getTotalVendas(int mes);

    Double getTotalFaturacaoMesFilial(int mes, int filial);
}
