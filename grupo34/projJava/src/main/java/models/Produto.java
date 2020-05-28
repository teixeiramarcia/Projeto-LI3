package models;

import utils.Pair;

import java.util.*;
import java.util.stream.Collectors;

/**
 * {@inheritDoc}
 */

public class Produto extends Model implements IProduto {
    private final String productID;
    private final List<Integer> vezes_comprado;
    private final List<Map<String, IComprasEFaturacao>> clientes_que_compraram;
    private final double[][] faturacao_mes_filial = new double[3][12];

    public Produto(String productID) {
        this.productID = productID;
        this.vezes_comprado = new ArrayList<>(12);
        this.clientes_que_compraram = new ArrayList<>(12);
        for (int mes = 0; mes < 12; mes++) {
            this.vezes_comprado.add(0);
            this.clientes_que_compraram.add(mes, new HashMap<>());
        }
    }

    @Override
    public String getProductID() {
        return productID;
    }

    @Override
    public void updateProduto(IVenda venda) {
        this.vezes_comprado.set(venda.getMes(), this.vezes_comprado.get(venda.getMes()) + 1);
        this.faturacao_mes_filial[venda.getFilial()][venda.getMes()] += venda.getFaturacao();

        Map<String, IComprasEFaturacao> clientes_mes = this.clientes_que_compraram.get(venda.getMes());
        if (!clientes_mes.containsKey(venda.getClientID())) {
            clientes_mes.put(venda.getClientID(), new ComprasEFaturacao(venda.getUnidades(), venda.getFaturacao()));
        } else {
            IComprasEFaturacao anterior = clientes_mes.get(venda.getClientID());
            anterior.addCompras(venda.getUnidades());
            anterior.addFaturacao(venda.getFaturacao());
        }
    }

    @Override
    public boolean wasntBoughtGeneral() {
        for (int mes = 0; mes < 12; mes++) {
            if (this.vezes_comprado.get(mes) != 0) return false;
        }
        return true;
    }

    @Override
    public List<Integer> getMonthlyBuyings() {
        return this.vezes_comprado;
    }

    @Override
    public List<Integer> getClients() {
        List<Integer> resultado = new ArrayList<>();
        for (int mes = 0; mes < 12; mes++) {
            resultado.add(mes, this.clientes_que_compraram.get(mes).size());
        }
        return resultado;
    }

    @Override
    public List<Double> getTotalBilling() {
        List<Double> resultado = new ArrayList<>();
        for (int mes = 0; mes < 12; mes++) {
            double fat_mes = 0;
            for (int filial = 0; filial < 3; filial++) {
                fat_mes += this.faturacao_mes_filial[filial][mes];
            }
            resultado.add(mes, fat_mes);
        }
        return resultado;
    }

    @Override
    public int getDistinctClients() {
        Set<String> clientes = new TreeSet<>();
        this.clientes_que_compraram.forEach(clientes_mes -> clientes.addAll(clientes_mes.keySet()));
        return clientes.size();
    }

    @Override
    public List<Pair<String, Double>> getTopNClients(int n) {
        List<Pair<String, IComprasEFaturacao>> resultado = new ArrayList<>();
        Map<String, IComprasEFaturacao> clientes = new HashMap<>();

        for (Map<String, IComprasEFaturacao> clientes_mes : this.clientes_que_compraram) {
            clientes_mes.forEach((k, v) -> {
                if (!clientes.containsKey(k)) {
                    clientes.put(k, v);
                } else {
                    IComprasEFaturacao ant = clientes.get(k);
                    ant.addCompras(v.getVezes_comprado());
                    ant.addFaturacao(v.getFaturacao());
                }
            });
        }

        clientes.forEach((k, v) -> resultado.add(Pair.of(k, v)));

        Comparator<Pair<String, IComprasEFaturacao>> comparator = Comparator.comparingInt(p -> p.getSecond().getVezes_comprado());
        return resultado.stream()
                .sorted(comparator.reversed())
                .limit(n)
                .map(p -> Pair.of(p.getFirst(), p.getSecond().getFaturacao()))
                .collect(Collectors.toList());
    }

    @Override
    public Pair<String, List<Double>> getFaturacaoMesFilial() {
        List<Double> resultado = new ArrayList<>();
        for (int filial = 0; filial < 3; filial++) {
            for (int mes = 0; mes < 12; mes++) {
                resultado.add(this.faturacao_mes_filial[filial][mes]);
            }
        }
        return Pair.of(this.productID, resultado);
    }
}
