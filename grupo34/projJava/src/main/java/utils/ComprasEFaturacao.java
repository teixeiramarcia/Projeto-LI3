package utils;

public class ComprasEFaturacao {
    private int vezes_comprado;
    private double faturacao;

    public ComprasEFaturacao(int vezes_comprado, double faturacao) {
        this.vezes_comprado = vezes_comprado;
        this.faturacao = faturacao;
    }

    public int getVezes_comprado() {
        return vezes_comprado;
    }

    public double getFaturacao() {
        return faturacao;
    }

    public void addCompras(int n) {
        this.vezes_comprado += n;
    }

    public void addFaturacao(double n) {
        this.faturacao += n;
    }
}
