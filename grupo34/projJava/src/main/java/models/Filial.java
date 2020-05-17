package models;

import java.util.Arrays;
import java.util.Comparator;

import static java.util.Comparator.comparingDouble;

public class Filial implements IFilial {
    private final ICliente[] top_3_I_clientes = new ICliente[3];
    private int clientes_so_far;

    public Filial() {
        this.clientes_so_far = 0;
    }

    @Override
    public void updateFilial(IVenda IVenda, ICliente ICliente) {
        Comparator<ICliente> c = comparingDouble(a -> a.getFaturacaoFilial(IVenda.getFilial()));
        if (this.clientes_so_far > 2) {
            double faturacao_ultimo_cliente = top_3_I_clientes[2].getFaturacaoFilial(IVenda.getFilial());
            double faturacao_cliente_novo = ICliente.getFaturacaoFilial(IVenda.getFilial());
            if (faturacao_ultimo_cliente > faturacao_cliente_novo) {
                return;
            }
            this.top_3_I_clientes[2] = ICliente;
            Arrays.sort(this.top_3_I_clientes, c.reversed());
        } else if (this.clientes_so_far < 2) {
            this.top_3_I_clientes[this.clientes_so_far] = ICliente;
            Arrays.sort(this.top_3_I_clientes, 0, clientes_so_far, c.reversed());
            this.clientes_so_far++;
        }
    }
}