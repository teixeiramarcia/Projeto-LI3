package models;

import java.util.Arrays;
import java.util.Comparator;

import static java.util.Comparator.comparingDouble;

public class Filial {
    private final Cliente[] top_3_clientes = new Cliente[3];
    private int clientes_so_far;

    public Filial() {
        this.clientes_so_far = 0;
    }

    public void updateFilial(Venda venda, Cliente cliente) {
        Comparator<Cliente> c = comparingDouble(a -> a.getFaturacaoFilial(venda.getFilial()));
        if(this.clientes_so_far > 2) {
            double faturacao_ultimo_cliente = top_3_clientes[2].getFaturacaoFilial(venda.getFilial());
            double faturacao_cliente_novo = cliente.getFaturacaoFilial(venda.getFilial());
            if(faturacao_ultimo_cliente > faturacao_cliente_novo) {
                return;
            }
            this.top_3_clientes[2] = cliente;
            Arrays.sort(this.top_3_clientes, c.reversed());
        } else if (this.clientes_so_far < 2) {
            this.top_3_clientes[this.clientes_so_far] = cliente;
            Arrays.sort(this.top_3_clientes, 0, clientes_so_far, c.reversed());
            this.clientes_so_far++;
        }
    }
}