package models;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.regex.Pattern;

public class Produto {
    private static final Pattern pattern = Pattern.compile("[A-Z]{2}[1-9]\\d{3}");

    private final String productID;
    private final int[] vezes_comprado = new int[12];
    private final List<Set<String>> clientes_que_compraram;
    private final double[] faturacao = new double[12];

    public Produto(String productID) {
        this.productID = productID;
        this.clientes_que_compraram = new ArrayList<>(12);
        for (int mes=0; mes < 12; mes++) {
            this.clientes_que_compraram.add(mes, new HashSet<>());
        }
    }

    public static boolean validaProduto(String line) {
        String pieces = line.trim();
        return pattern.matcher(pieces).matches();
    }

    public String getProductID() {
        return productID;
    }

    public void updateProduto(Venda venda) {
        this.vezes_comprado[venda.getMes()] += venda.getUnidades();
        this.clientes_que_compraram.get(venda.getMes()).add(venda.getClientID());
        this.faturacao[venda.getMes()] += venda.getFaturacao();
    }

    public boolean wasntBoughtGeneral() {
        for (int mes = 0; mes < 12; mes++) {
            if(this.vezes_comprado[mes] != 0) return false;
        }
        return true;
    }
}
