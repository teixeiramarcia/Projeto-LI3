package models;

public class Filiais {
    private final Filial[] filiais;


    public Filiais() {
        this.filiais = new Filial[3];
        for (int filial = 0; filial < 3; filial++)
            this.filiais[filial] = new Filial();
    }

    public void updateFiliais(Venda venda, Cliente cliente) {
        this.filiais[venda.getFilial()].updateFilial(venda, cliente);
    }
}
