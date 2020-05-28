package models;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;
import java.util.stream.Collectors;

/**
 * {@inheritDoc}
 */

public class Filial extends Model implements IFilial {
    private final int filial;
    private List<ICliente> top_3_clientes;

    public Filial(int filial) {
        this.filial = filial;
        this.top_3_clientes = new ArrayList<>();
    }

    @Override
    public void updateFilial(IVenda venda, ICliente cliente) {
        Comparator<ICliente> comparator = Comparator.comparingDouble(cli -> cli.getFaturacaoFilial(filial));
        if (!this.top_3_clientes.contains(cliente)) {
            this.top_3_clientes.add(cliente);

            this.top_3_clientes = this.top_3_clientes.stream()
                    .sorted(comparator.reversed())
                    .limit(3)
                    .collect(Collectors.toList());
        }
    }

    @Override
    public String[] getTop3Buyers() {
        Comparator<ICliente> comparator = Comparator.comparingDouble(cli -> cli.getFaturacaoFilial(filial));
        String[] resultado = new String[this.top_3_clientes.size()];
        int indice = 0;
        for (Iterator<ICliente> it = this.top_3_clientes.stream().sorted(comparator.reversed()).iterator(); it.hasNext(); ) {
            ICliente cliente = it.next();
            resultado[indice++] = cliente.getClientID();
        }
        return resultado;
    }
}