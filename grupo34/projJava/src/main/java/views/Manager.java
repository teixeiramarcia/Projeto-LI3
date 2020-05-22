package views;

import controllers.GestVendasController;
import controllers.IGestVendasController;
import models.*;
import utils.Chrono;
import utils.Pair;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Manager {
    private final Input inputClass;
    private final IGestVendasController gestVendasController;
    private final String path_to_files;
    private final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));


    public Manager(String path_to_files) {
        this.gestVendasController = new GestVendasController();
        this.inputClass = new Input(gestVendasController);
        this.path_to_files = path_to_files;
    }

    public void loadOptionsMenu() throws IOException {
        boolean errors = true;
        while (errors) {
            printLoadOptions();
            errors = false;
            String input = br.readLine();
            System.out.print("\033\143");
            switch (input) {
                case "1":
                    this.gestVendasController.loadSGVFromFiles(this.path_to_files, "Vendas_1M.txt");
                    break;
                case "2":
                    this.gestVendasController.loadSGVFromFiles(this.path_to_files, "Vendas_3M.txt");
                    break;
                case "3":
                    this.gestVendasController.loadSGVFromFiles(this.path_to_files, "Vendas_5M.txt");
                    break;
                case "4":
                    this.gestVendasController.loadSGVFromFiles(this.path_to_files, "dat");
                    break;
                case "5":
                    System.exit(0);
                    break;
                default:
                    errors = true;
                    System.out.println(getLoadOptInvalidoMenu());

            }
        }
    }

    public void start() {
        System.out.print("\033\143");
        try {
            loadOptionsMenu();
            menu();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void menu() throws IOException {
        boolean flagCycle = true;
        boolean no_errors = true;
        while (flagCycle) {
            if (no_errors) {
                System.out.print(getMenu());
            } else {
                System.out.println(getInputInvalidoMenu());
                no_errors = true;
            }
            String input = br.readLine();
            System.out.print("\033\143");
            switch (input) {
                case "1":
                    query1();
                    break;
                case "2":
                    query2(inputClass.getInputMonth());
                    printPreviousMenuOpt();
                    break;
                case "3":
                    query3(inputClass.getInputClient());
                    printPreviousMenuOpt();
                    break;
                case "4":
                    query4(inputClass.getInputProduct());
                    printPreviousMenuOpt();
                    break;
                case "5":
                    query5(inputClass.getInputClient());
                    break;
                case "6":
                    query6(inputClass.getInputInt());
                    break;
                case "7":
                    query7();
                    printPreviousMenuOpt();
                    break;
                case "8":
                    query8(inputClass.getInputInt());
                    break;
                case "9":
                    query9(inputClass.getInputProduct(), inputClass.getInputInt());
                    break;
                case "10":
                    query10();
                    break;
                case "11":
                    printStatisticsMenu();
                    printPreviousMenuOpt();
                    break;
                case "12":
                    loadOptionsMenu();
                    break;
                case "13":
                    this.gestVendasController.saveProgramStatus(this.path_to_files);
                    break;
                case "0":
                    flagCycle = false;
                    break;
                default:
                    no_errors = false;
                    break;
            }
        }
    }

    private String getMenu() {
        return "\033\143" +
                Colors.BLUE +
                "\n" + String.join("", Collections.nCopies(50, "―")) + " SISTEMA DE GESTÃO DE VENDAS " + String.join("", Collections.nCopies(50, "―")) + "\n\n" +
                Colors.RESET +
                Colors.YELLOW +
                "Escolha uma opção:\n\n" +
                Colors.RESET +
                yellowNumber(1) + "Lista alfabeticamente ordenada dos códigos de produtos que nunca foram comprados e respetivo total\n" +
                yellowNumber(2) + "Listagem do número total de compras e o número total de clientes distintos envolvidos\n" +
                yellowNumber(3) + "Listagem mensal do total de compras, total de produtos comprados e total gasto por um determinado cliente\n" +
                yellowNumber(4) + "Listagem mensal do total de vendas, total de clientes envolvidos e total faturado de um determinado produto\n" +
                yellowNumber(5) + "Listagem de produtos mais comprados por um determinado cliente\n" +
                yellowNumber(6) + "Listagem dos N produtos mais vendidos e respetiva contagem de clientes distintos que os compraram\n" +
                yellowNumber(7) + "Listagem dos 3 maiores compradores em cada filial\n" +
                yellowNumber(8) + "Top N clientes que compraram uma maior quantidade de produtos diferentes\n" +
                yellowNumber(9) + "Top N clientes que mais compraram um determinado produto\n" +
                yellowNumber(10) + "Contagem mês a mês e filial a filial da faturação total do sistema\n" +
                yellowNumber(11) + "Consultas estatísticas\n" +
                yellowNumber(12) + "Carregamento de dados\n" +
                yellowNumber(13) + "Gravar estado do programa\n" +
                yellowNumber(0) + "Sair do programa\n" +
                "\n\n" +
                Colors.BLUE +
                "Input -->  " +
                Colors.RESET;
    }

    private void printLoadOptions() {
        System.out.println(Colors.BLUE +
                "\n" + String.join("", Collections.nCopies(15, "―")) + " Carregamento do Sistema " + String.join("", Collections.nCopies(15, "―")) + "\n\n" +
                Colors.RESET);
        System.out.println(yellowNumber(1) + "Ler o ficheiro 'Vendas_1M.txt'.");
        System.out.println(yellowNumber(2) + "Ler o ficheiro 'Vendas_3M.txt'.");
        System.out.println(yellowNumber(3) + "Ler o ficheiro 'Vendas_5M.txt'.");
        System.out.println(yellowNumber(4) + "Carregamento de dados a partir do ficheiro .dat.");
        System.out.println(yellowNumber(5) + "Sair do programa.\n");
        System.out.print(Colors.BLUE + "Input -> " + Colors.RESET);
    }

    private String yellowNumber(int i) {
        return Colors.YELLOW + " " + i + " -> " + Colors.RESET;
    }

    private String getLoadOptInvalidoMenu() {
        return Colors.RED +
                "Input inválido.\nIndique um dígito entre 1 e 5\n" +
                Colors.RESET;
    }

    private String getInputInvalidoMenu() {
        return Colors.RED +
                "Input inválido.\nIndique um dígito entre 0 e 13\n" +
                "Input -->  " +
                Colors.RESET;
    }

    private void printPreviousMenuOpt() throws IOException {
        System.out.println("\n");
        System.out.println(Colors.BLUE + "Q -> voltar ao menu principal");
        System.out.print("-> " + Colors.RESET);
        String i = br.readLine();
        while (!i.equals("Q") && !i.equals("q")) {
            System.out.println("\n");
            System.out.println(Colors.RED + "Q -> voltar ao menu principal");
            System.out.print("-> " + Colors.RESET);
        }
    }

    private void query1() throws IOException {
        printQuery1(getQuery1Data());
    }

    public Pair<List<String>, String> getQuery1Data() {
        return Chrono.chronoMe(gestVendasController::getProdutosNuncaComprados);
    }

    private void printQuery1(Pair<List<String>, String> p) throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " Listagem dos códigos de produtos nunca comprados e respetivo total " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        List<String> produtos_nunca_comprados = p.getFirst();
        Navegador.printer(produtos_nunca_comprados, titulo, p.getSecond());
    }

    private void query2(int mes) {
        printQuery2(getQuery2Data(mes));
    }

    public Pair<Pair<Integer, Integer>, String> getQuery2Data(int mes) {
        return Chrono.chronoMe(() -> {
            int total_vendas = gestVendasController.getTotalVendas(mes);
            int total_clientes = gestVendasController.getNumClientesCompraramNoMes(mes);
            return Pair.of(total_vendas, total_clientes);
        });
    }

    private void printQuery2(Pair<Pair<Integer, Integer>, String> p) {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " Total de vendas realizadas e total de clientes envolvidos num determinado mês " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        System.out.println(Colors.YELLOW +
                "Total de vendas realizadas: " +
                Colors.RESET +
                p.getFirst().getFirst());
        System.out.println(Colors.YELLOW +
                "Total de clientes (distintos) envolvidos: " +
                Colors.RESET +
                p.getFirst().getSecond());
        System.out.println(p.getSecond());
    }

    private void query3(String clientID) {
        printQuery3(getQuery3Data(clientID));
    }

    public Pair<QWithTablesHelper, String> getQuery3Data(String clientID) {
        return Chrono.chronoMe(() -> {
            QWithTablesHelper q = new QWithTablesHelper();
            q.a = gestVendasController.getClientMonthlyBuyings(clientID);
            q.b = gestVendasController.getClientMonthlyProducts(clientID);
            q.c = gestVendasController.getMonthlyTotalCost(clientID);
            return q;
        });
    }

    private void printQuery3(Pair<QWithTablesHelper, String> p) {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " Listagem mensal do número de compras, número de produtos (distintos) e total gasto por um determinado cliente " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        System.out.print(String.format("%6s", ""));
        printMonths();
        System.out.print(Colors.BLUE);
        System.out.println(String.join("", Collections.nCopies(172, "―")));
        System.out.print(Colors.RESET);
        printLineInt(p.getFirst().a,
                String.format("%10s",
                        Colors.YELLOW + "Nums ｜" + Colors.RESET));
        printLineInt(p.getFirst().b,
                String.format("%10s",
                        Colors.YELLOW + "Prods｜" + Colors.RESET));
        printLineDouble(p.getFirst().c,
                String.format("%10s",
                        Colors.YELLOW + "Gasto｜" + Colors.RESET));
        System.out.println(p.getSecond());
    }

    private void query4(String productID) {
        printQuery4(getQuery4Data(productID));
    }

    public Pair<QWithTablesHelper, String> getQuery4Data(String productID) {
        return Chrono.chronoMe(() -> {
            QWithTablesHelper q = new QWithTablesHelper();
            q.a = gestVendasController.getProductMonthlyBuyings(productID);
            q.b = gestVendasController.getProductClients(productID);
            q.c = gestVendasController.getProductBilling(productID);
            return q;
        });
    }

    private void printQuery4(Pair<QWithTablesHelper, String> p) {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " Total de vezes que o produto foi comprado, número clientes (distintos) envolvidos e total faturado " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        System.out.print(String.format("%6s", ""));
        printMonths();
        System.out.print(Colors.BLUE);
        System.out.println(String.join("", Collections.nCopies(172, "―")));
        System.out.print(Colors.RESET);
        printLineInt(p.getFirst().a,
                String.format("%10s",
                        Colors.YELLOW + "Nums ｜" + Colors.RESET));
        printLineInt(p.getFirst().b,
                String.format("%10s",
                        Colors.YELLOW + "Clis ｜" + Colors.RESET));
        printLineDouble(p.getFirst().c,
                String.format("%10s",
                        Colors.YELLOW + "Fat  ｜" + Colors.RESET));
        System.out.println(p.getSecond());
    }

    private void query5(String clientID) throws IOException {
        printQuery5(getQuery5Data(clientID));
    }

    public Pair<List<String>, String> getQuery5Data(String clientID) {
        return Chrono.chronoMe(() -> gestVendasController.getClientFavoriteProducts(clientID));
    }

    private void printQuery5(Pair<List<String>, String> p) throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " Listagem dos códigos de produtos favoritos de um determinado cliente e respetivo total " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        List<String> produtos_mais_comprados = p.getFirst();
        Navegador.printer(produtos_mais_comprados, titulo, p.getSecond());
    }

    private void query6(int n) throws IOException {
        printQuery6(getQuery6Data(n));
    }

    public Pair<List<IProdutoQuantidade>, String> getQuery6Data(int n) {
        return Chrono.chronoMe(() -> gestVendasController.getTopNProducts(n).stream()
                .map(ProdutoQuantidade::new)
                .collect(Collectors.toList()));
    }

    private void printQuery6(Pair<List<IProdutoQuantidade>, String> p) throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(50, "―")) + " Top X produtos que mais clientes distintos compraram " +
                String.join("", Collections.nCopies(50, "―")) + Colors.RESET + "\n");
        List<IProdutoQuantidade> top_n = p.getFirst();
        Navegador.printer(top_n, titulo, p.getSecond());
    }

    private void query7() {
        printQuery7(getQuery7Data());
    }

    public Pair<String[][], String> getQuery7Data() {
        return Chrono.chronoMe(this.gestVendasController::getTop3Buyers);
    }

    private void printQuery7(Pair<String[][], String> p) {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " 3 maiores compradores separados por filial " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        String[][] top3 = p.getFirst();
        for (int filial = 0; filial < 3; filial++) {
            System.out.println(Colors.YELLOW + "Filial " + (filial + 1) + Colors.RESET);
            for (int cliente = 0; cliente < top3[filial].length; cliente++) {
                System.out.print(Colors.YELLOW + "-> " + Colors.RESET);
                System.out.println(top3[filial][cliente]);
            }
            System.out.println();
        }
        System.out.println(p.getSecond());
    }

    private void query8(int n) throws IOException {
        printQuery8(getQuery8Data(n));
    }

    public Pair<List<IClientesQuantidade>, String> getQuery8Data(int n) {
        return Chrono.chronoMe(() -> gestVendasController.getTopNClients(n).stream()
                .map(ClientesQuantidade::new)
                .collect(Collectors.toList()));
    }

    private void printQuery8(Pair<List<IClientesQuantidade>, String> p) throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(50, "―")) + " Top X clientes que compraram mais produtos distintos " +
                String.join("", Collections.nCopies(50, "―")) + Colors.RESET + "\n");
        List<IClientesQuantidade> top_n = p.getFirst();
        Navegador.printer(top_n, titulo, p.getSecond());
    }

    private void query9(String productID, int n) throws IOException {
        printQuery9(getQuery9Data(productID, n));
    }

    public Pair<List<IClienteFaturacaoNoProduto>, String> getQuery9Data(String productID, int n) {
        return Chrono.chronoMe(() -> gestVendasController.getTopNClientsOfProduct(productID, n).stream()
                .map(ClienteFaturacaoNoProduto::new)
                .collect(Collectors.toList()));
    }

    private void printQuery9(Pair<List<IClienteFaturacaoNoProduto>, String> p) throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(10, "―")) + " Top X clientes que mais compraram um determinado produto e para cada, o valor gasto " +
                String.join("", Collections.nCopies(10, "―")) + Colors.RESET + "\n");
        List<IClienteFaturacaoNoProduto> top_n = p.getFirst();
        Navegador.printer(top_n, titulo, p.getSecond());
    }

    private void query10() throws IOException {
        Pair<List<Pair<String, List<Double>>>, String> p = getQuery10Data();
        List<Pair<String, List<Double>>> faturacao_mes_filial = parseQuery10Data(p);

        printQuery10(faturacao_mes_filial, p);
    }

    public List<Pair<String, List<Double>>> parseQuery10Data(Pair<List<Pair<String, List<Double>>>, String> p) {
        return p.getFirst()
                .stream()
                .filter(par -> par.getSecond().stream().anyMatch(d -> d != 0))
                .collect(Collectors.toList());
    }

    public Pair<List<Pair<String, List<Double>>>, String> getQuery10Data() {
        return Chrono.chronoMe(gestVendasController::getFaturacaoPorProduto);
    }

    private void printQuery10(List<Pair<String, List<Double>>> faturacao_mes_filial, Pair<List<Pair<String, List<Double>>>, String> p) throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(69, "―")) + "Faturação total por mês e por filial para cada produto" +
                String.join("", Collections.nCopies(69, "―")) + Colors.RESET + "\n");

        NavegadorQuery10.printer(faturacao_mes_filial, titulo, p.getSecond());
    }

    private void printLastSalesFileInfo() {
        System.out.println(Colors.YELLOW + "Dados referentes ao último ficheiro de vendas lido:" + Colors.RESET);
        System.out.println("\n");
        System.out.println(Colors.YELLOW + "Nome do ficheiro -> " + Colors.RESET + gestVendasController.getLastSalesFileName());
        System.out.println(Colors.YELLOW + "Registos de vendas errados -> " + Colors.RESET + gestVendasController.getWrongSales());
        System.out.println(Colors.YELLOW + "Total de produtos -> " + Colors.RESET + gestVendasController.getTotalProducts());
        System.out.println(Colors.YELLOW + "Total de produtos distintos comprados -> " + Colors.RESET + gestVendasController.getTotalDistinctBoughtProducts());
        System.out.println(Colors.YELLOW + "Total de produtos não comprados ->" + Colors.RESET + gestVendasController.getTotalNeverBoughtProducts());
        System.out.println(Colors.YELLOW + "Total de clientes -> " + Colors.RESET + gestVendasController.getTotalClients());
        System.out.println(Colors.YELLOW + "Total de clientes que efetuaram compras -> " + Colors.RESET + gestVendasController.getTotalBuyingClients());
        System.out.println(Colors.YELLOW + "Total de clientes que nunca efeturam compras -> " + Colors.RESET + gestVendasController.getNeverBuyingClients());
        System.out.println(Colors.YELLOW + "Total de compras de valor 0.0 -> " + Colors.RESET + gestVendasController.getZeroSales());
        System.out.println(Colors.YELLOW + "Faturação total -> " + Colors.RESET + String.format("%10.2f", gestVendasController.getTotalBilling()));
        System.out.println();
    }

    private void printMonths() {
        for (String month : Meses.meses) {
            System.out.printf(Colors.YELLOW + "%12s" + Colors.BLUE + "｜" + Colors.RESET, month);
        }
        System.out.print("\n");
    }

    private void printSales(Map<String, Integer> sales_per_month) {
        for (String mes : Meses.meses) {
            Integer faturacao = sales_per_month.get(mes);
            System.out.printf("%12d" + Colors.BLUE + "｜" + Colors.RESET, faturacao);
        }
        System.out.println("\n");
    }

    private void printMonthlySales() {
        System.out.println(Colors.YELLOW + "Total de compras por mês:\n" + Colors.RESET);
        printMonths();
        String line = String.join("", Collections.nCopies(166, "―"));
        System.out.println(Colors.BLUE + line + Colors.RESET);
        printSales(gestVendasController.getTotalCompras());
    }

    private double printFaturacaoMesFilial(Map<String, Map<Integer, Double>> table_contents) {
        System.out.printf("%3s" + Colors.BLUE + " ｜ " + Colors.YELLOW + "%13s ｜ %13s ｜ %13s ｜\n", "", "Filial 1", "Filial 2", "Filial 3");
        System.out.print(Colors.RESET);
        System.out.print(Colors.BLUE);
        System.out.println(String.join("", Collections.nCopies(57, "―")));
        System.out.print(Colors.RESET);
        double faturacao_global = 0;
        for (String mes : Meses.meses) {
            String line = "";
            line += Colors.YELLOW + mes + Colors.BLUE + " ｜ " + Colors.RESET;

            Map<Integer, Double> faturacao_mes = table_contents.get(mes);
            line += String.format("%10.2f", faturacao_mes.get(1)) + Colors.YELLOW + " ｜ " + Colors.RESET;
            line += String.format("%10.2f", faturacao_mes.get(2)) + Colors.YELLOW + " ｜ " + Colors.RESET;
            line += String.format("%10.2f", faturacao_mes.get(3)) + Colors.YELLOW + " ｜ " + Colors.RESET;
            faturacao_global += faturacao_mes.get(1) + faturacao_mes.get(2) + faturacao_mes.get(3);

            System.out.println(line);
        }
        return faturacao_global;
    }

    private void printMonthlyBilling() {
        System.out.println(Colors.YELLOW + "\n\nFaturação total por mês e por filial:\n" + Colors.RESET);
        double faturacao_global = printFaturacaoMesFilial(gestVendasController.getTotalFaturacao());
        System.out.print(Colors.YELLOW + "\nFaturacao global: " + Colors.RESET);
        System.out.print(String.format("%10.2f", faturacao_global));
    }

    private void printNumClientesMesFilial(Map<String, Map<Integer, Integer>> table_contents) {
        System.out.printf("%3s" + Colors.BLUE + " ｜ " + Colors.YELLOW + "%8s ｜ %8s ｜ %8s ｜\n", "", "Filial 1", "Filial 2", "Filial 3");
        System.out.print(Colors.RESET);
        System.out.print(Colors.BLUE);
        System.out.println(String.join("", Collections.nCopies(42, "―")));
        System.out.print(Colors.RESET);
        for (String mes : Meses.meses) {
            String line = "";
            line += Colors.YELLOW + mes + Colors.BLUE + " ｜ " + Colors.RESET;

            Map<Integer, Integer> clientes_mes = table_contents.get(mes);
            line += String.format("%8d", clientes_mes.get(1)) + Colors.YELLOW + " ｜ " + Colors.RESET;
            line += String.format("%8d", clientes_mes.get(2)) + Colors.YELLOW + " ｜ " + Colors.RESET;
            line += String.format("%8d", clientes_mes.get(3)) + Colors.YELLOW + " ｜ " + Colors.RESET;

            System.out.println(line);
        }
    }

    private void printMonthlyMonthlyClients() {
        System.out.println(Colors.YELLOW + "\n\nTotal de clientes que efetuaram compras por mês e por filial:\n" + Colors.RESET);
        printNumClientesMesFilial(gestVendasController.getNumClientesCompraramFilialPorMes());
    }

    private void printStatisticsMenu() {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(45, "―")) + " Estatísticas: " +
                String.join("", Collections.nCopies(46, "―")) + Colors.RESET + "\n\n");
        printLastSalesFileInfo();
        printMonthlySales();
        printMonthlyBilling();
        printMonthlyMonthlyClients();
        System.out.println("\n");
    }

    private void printLineInt(List<Integer> linha, String titulo) {
        StringBuilder nums = new StringBuilder(titulo);
        for (int mes = 0; mes < 12; mes++) {
            nums.append(String.format("%10d", linha.get(mes))).append(Colors.BLUE).append(" ｜ ").append(Colors.RESET);
        }
        System.out.println(nums);
    }

    private void printLineDouble(List<Double> linha, String titulo) {
        StringBuilder nums = new StringBuilder(titulo);
        for (int mes = 0; mes < 12; mes++) {
            nums.append(String.format("%10.2f", linha.get(mes))).append(Colors.BLUE).append(" ｜ ").append(Colors.RESET);
        }
        System.out.println(nums);
    }

    private static class QWithTablesHelper {
        private List<Integer> a;
        private List<Integer> b;
        private List<Double> c;
    }


}
