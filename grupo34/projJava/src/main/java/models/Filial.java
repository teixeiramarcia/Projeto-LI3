package models;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Filial implements IFilial {
    private final int filial;
    private List<ICliente> top_3_clientes;
    private final Comparator<ICliente> comparator;

    public Filial(int filial) {
        this.filial = filial;
        this.top_3_clientes = new ArrayList<>();
        this.comparator = Comparator.comparingDouble(cliente -> cliente.getFaturacaoFilial(filial));
    }

    @Override
    public void updateFilial(IVenda venda, ICliente cliente) {
        if(!this.top_3_clientes.contains(cliente)) {
            this.top_3_clientes.add(cliente);

            this.top_3_clientes = this.top_3_clientes.stream()
                    .sorted(comparator.reversed())
                    .limit(3)
                    .collect(Collectors.toList());
        }
    }

    public String[] getTop3Buyers() {
        String[] resultado = new String[this.top_3_clientes.size()];
        int indice = 0;
        for (Iterator<ICliente> it = this.top_3_clientes.stream().sorted(comparator.reversed()).iterator(); it.hasNext(); ) {
            ICliente cliente = it.next();
            resultado[indice++] = cliente.getClientID();
        }
        return resultado;
    }
}