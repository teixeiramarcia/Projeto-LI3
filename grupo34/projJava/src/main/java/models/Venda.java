package models;

import java.io.InvalidClassException;

public class Venda {
    private final String codigo_produto;
    private final double preco_unitario;
    private final int unidades;
    private final String codigo_cliente;
    private final int mes;
    private final int filial;

    public Venda(String venda_completa, GestVendas gestVendas) throws InvalidClassException {
        String[] pieces = venda_completa.replace("(\\r\\n)", "").split(" ");

        if (!validaVenda(pieces, gestVendas)) {
            throw new InvalidClassException("Venda Inválida");
        }

        this.codigo_produto = pieces[0];
        this.preco_unitario = Double.parseDouble(pieces[1]);
        this.unidades = Integer.parseInt(pieces[2]);
        this.codigo_cliente = pieces[4];
        this.mes = Integer.parseInt(pieces[5]) - 1;
        this.filial = Integer.parseInt(pieces[6]) - 1;
    }

    public int getMes() {
        return this.mes;
    }

    public String getClientID() {
        return this.codigo_cliente;
    }

    public String getProductID() {
        return this.codigo_produto;
    }

    public int getFilial() {
        return this.filial;
    }

    public int getUnidades() {
        return this.unidades;
    }

    public double getFaturacao() {
        return this.preco_unitario * this.unidades;
    }

    public static boolean validaVenda(String[] pieces, GestVendas gestVendas) {
        return
                Produto.validaProduto(pieces[0]) &&
                        gestVendas.existeProduto(pieces[0]) &&
                        Cliente.validaCliente(pieces[4]) &&
                        gestVendas.existeCliente(pieces[4]);
    }

}