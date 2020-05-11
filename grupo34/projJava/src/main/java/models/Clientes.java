package models;

import java.util.HashMap;
import java.util.Map;

public class Clientes {
    private final Map<String, Cliente> clientes;

    public Clientes() {
        this.clientes = new HashMap<>();
    }

    public Cliente getClient(Venda venda) {
        return this.clientes.get(venda.getClientID());
    }

    public boolean existeCliente(String clientID) {
        return this.clientes.containsKey(clientID);
    }

    public void addClient(Cliente cliente) {
        this.clientes.put(cliente.getClientID(), cliente);
    }

    public void updateClientes(Venda venda) {
        this.clientes.get(venda.getClientID()).updateCliente(venda);
    }

    public int getTotalClientesFilialMes(int filial, int mes) {
        int resultado = 0;
        for (Cliente cliente: clientes.values())
            if(cliente.faturouNaFilial(filial) && cliente.comprouNoMes(mes))
                resultado++;
        return resultado;
    }
}
