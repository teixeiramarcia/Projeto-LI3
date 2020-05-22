package models;

import java.io.InvalidClassException;

public class Venda extends Model implements IVenda {
    private final String codigo_produto;
    private final double preco_unitario;
    private final int unidades;
    private final String codigo_cliente;
    private final int mes;
    private final int filial;

    public Venda(String venda_completa, IGestVendas IGestVendas) throws InvalidClassException {
        String[] pieces = venda_completa.replace("(\\r\\n)", "").split(" ");

        if (!validaVenda(pieces, IGestVendas)) {
            throw new InvalidClassException("Venda Inválida");
        }

        this.codigo_produto = pieces[0];
        this.preco_unitario = Double.parseDouble(pieces[1]);
        this.unidades = Integer.parseInt(pieces[2]);
        this.codigo_cliente = pieces[4];
        this.mes = Integer.parseInt(pieces[5]) - 1;
        this.filial = Integer.parseInt(pieces[6]) - 1;
    }

    static boolean validaVenda(String[] pieces, IGestVendas IGestVendas) {
        return IProduto.validaProduto(pieces[0]) &&
                IGestVendas.existeProduto(pieces[0]) &&
                ICliente.validaCliente(pieces[4]) &&
                IGestVendas.existeCliente(pieces[4]);
    }

    @Override
    public int getMes() {
        return this.mes;
    }

    @Override
    public String getClientID() {
        return this.codigo_cliente;
    }

    @Override
    public String getProductID() {
        return this.codigo_produto;
    }

    @Override
    public int getFilial() {
        return this.filial;
    }

    @Override
    public int getUnidades() {
        return this.unidades;
    }

    @Override
    public double getFaturacao() {
        return this.preco_unitario * this.unidades;
    }

}