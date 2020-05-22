package models;

public class ComprasEFaturacao extends Model implements IComprasEFaturacao {
    private int vezes_comprado;
    private double faturacao;

    public ComprasEFaturacao(int vezes_comprado, double faturacao) {
        this.vezes_comprado = vezes_comprado;
        this.faturacao = faturacao;
    }

    @Override
    public int getVezes_comprado() {
        return vezes_comprado;
    }

    @Override
    public double getFaturacao() {
        return faturacao;
    }

    @Override
    public void addCompras(int n) {
        this.vezes_comprado += n;
    }

    @Override
    public void addFaturacao(double n) {
        this.faturacao += n;
    }
}
