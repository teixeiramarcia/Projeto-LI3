package models;

public class Filiais implements IFiliais {
    private final IFilial[] filiais;


    public Filiais() {
        this.filiais = new IFilial[3];
        for (int filial = 0; filial < 3; filial++)
            this.filiais[filial] = new Filial(filial);
    }

    @Override
    public void updateFiliais(IVenda IVenda, ICliente ICliente) {
        this.filiais[IVenda.getFilial()].updateFilial(IVenda, ICliente);
    }

    public String[][] getTop3Buyers() {
        String[][] resultado = new String[3][];
        for (int filial = 0; filial < 3; filial++) {
            resultado[filial] = this.filiais[filial].getTop3Buyers();
        }
        return resultado;
    }
}
