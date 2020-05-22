package models;

public interface IComprasEFaturacao {
    int getVezes_comprado();

    double getFaturacao();

    void addCompras(int n);

    void addFaturacao(double n);
}
