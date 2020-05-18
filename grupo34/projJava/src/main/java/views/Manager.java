package views;

import controllers.GestVendasController;
import controllers.IGestVendasController;
import utils.Pair;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
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

    public void start() throws FileNotFoundException {
        this.gestVendasController.loadSGVFromFiles(this.path_to_files);
        try {
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
            System.out.println("\n");
            switch (input) {
                case "1":
                    printQuery1();
                    printPreviousMenuOpt();
                    break;
                case "2":
                    printQuery2(inputClass.getInputMonth());
                    printPreviousMenuOpt();
                    break;
                case "3":
                    printQuery3(inputClass.getInputClient());
                    printPreviousMenuOpt();
                    break;
                case "4":
                    printQuery4(inputClass.getInputProduct());
                    printPreviousMenuOpt();
                    break;
                case "5":
                    printQuery5(inputClass.getInputClient());
                    printPreviousMenuOpt();
                    break;
                case "6":
                    printQuery6(inputClass.getInputInt());
                    printPreviousMenuOpt();
                    break;
                case "7":
                    //q7
                    printPreviousMenuOpt();
                    break;
                case "8":
                    printQuery8(inputClass.getInputInt());
                    printPreviousMenuOpt();
                    break;
                case "9":
                    //q9
                    printPreviousMenuOpt();
                    break;
                case "10":
                    printQuery10();
                    printPreviousMenuOpt();
                    break;
                case "11":
                    printStatisticsMenu();
                    printPreviousMenuOpt();
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
        return Colors.BLUE +
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
                yellowNumber(10) + "Contagem mês a mês e filial a filial a faturação total do sistema\n" +
                yellowNumber(11) + "Consultas estatísticas\n" +
                yellowNumber(0) + "Sair do programa\n" +
                "\n\n" +
                Colors.BLUE +
                "Input -->  " +
                Colors.RESET;
    }

    private String yellowNumber(int i) {
        return Colors.YELLOW + " " + i + " -> " + Colors.RESET;
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

        while (!br.readLine().equals("Q")) {
            System.out.println("\n");
            System.out.println(Colors.RED + "Q -> voltar ao menu principal");
            System.out.print("-> " + Colors.RESET);
        }
    }

    private void printQuery1() throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(40, "―")) + " Listagem dos códigos de produtos nunca comprados e respetivo total " +
                String.join("", Collections.nCopies(40, "―")) + Colors.RESET + "\n");
        List<String> produtos_nunca_comprados = gestVendasController.getProdutosNuncaComprados();
        Navegador.printer(produtos_nunca_comprados, titulo);
    }

    private void printQuery2(int mes) {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " Total de vendas realizadas e total de clientes envolvidos num determinado mês " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        System.out.println(Colors.YELLOW +
                "Total de vendas realizadas: " +
                Colors.RESET +
                gestVendasController.getTotalVendas(mes));
        System.out.println(Colors.YELLOW +
                "Total de clientes (distintos) envolvidos: " +
                Colors.RESET +
                gestVendasController.getTotalClientes(mes));
    }

    private void printQuery3(String clientID) {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " Listagem mensal do número de compras, número de produtos (distintos) e total gasto por um determinado cliente " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        System.out.print(String.format("%6s", ""));
        printMonths();
        System.out.print(Colors.BLUE);
        System.out.println(String.join("", Collections.nCopies(172, "―")));
        System.out.print(Colors.RESET);
        printLineInt(gestVendasController.getClientMonthlyBuyings(clientID),
                String.format("%10s",
                        Colors.YELLOW + "Nums ｜" + Colors.RESET));
        printLineInt(gestVendasController.getClientMonthlyProducts(clientID),
                String.format("%10s",
                        Colors.YELLOW + "Prods｜" + Colors.RESET));
        printLineDouble(gestVendasController.getMonthlyTotalCost(clientID),
                String.format("%10s",
                        Colors.YELLOW + "Gasto｜" + Colors.RESET));
    }

    private void printQuery4(String productID) {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " Total de vezes que o produto foi comprado, número clientes (distintos) envolvidos e total faturado " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        System.out.print(String.format("%6s", ""));
        printMonths();
        printLineInt(gestVendasController.getProductMonthlyBuyings(productID),
                String.format("%10s",
                        Colors.YELLOW + "Nums ｜" + Colors.RESET));
        printLineInt(gestVendasController.getProductClients(productID),
                String.format("%10s",
                        Colors.YELLOW + "Clis ｜" + Colors.RESET));
        printLineDouble(gestVendasController.getProductBilling(productID),
                String.format("%10s",
                        Colors.YELLOW + "Fat  ｜" + Colors.RESET));
    }

    private void printQuery5(String clientID) throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(5, "―")) + " Listagem dos códigos de produtos favoritos de um determinado cliente e respetivo total " +
                String.join("", Collections.nCopies(5, "―")) + Colors.RESET + "\n");
        List<String> produtos_mais_comprados = gestVendasController.getClientFavoriteProducts(clientID);
        Navegador.printer(produtos_mais_comprados, titulo);
    }

    private void printQuery6(int n) throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(50, "―")) + " Top X produtos que mais clientes distintos compraram " +
                String.join("", Collections.nCopies(50, "―")) + Colors.RESET + "\n");
        List<ProdutosQuantidade> top_n = gestVendasController.getTopNProducts(n).stream()
                .map(ProdutosQuantidade::new)
                .collect(Collectors.toList());
        Navegador.printer(top_n, titulo);

    }

    private void printQuery8(int n) throws IOException {
        String titulo = ("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(50, "―")) + " Top X clientes que compraram mais produtos distintos " +
                String.join("", Collections.nCopies(50, "―")) + Colors.RESET + "\n");
        List<ClientesQuantidade> top_n = gestVendasController.getTopNClients(n).stream()
                .map(ClientesQuantidade::new)
                .collect(Collectors.toList());
        Navegador.printer(top_n, titulo);
    }

    private void printQuery10() {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(15, "―")) + " Faturação total por mês e por filial " +
                String.join("", Collections.nCopies(15, "―")) + Colors.RESET + "\n");
        printFaturacaoMesFilial(gestVendasController.getTotalFaturacao());
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
        printNumClientesMesFilial(gestVendasController.getTotalClientesMesFilial());
    }

    private void printStatisticsMenu() {
        System.out.println("\n" + Colors.BLUE +
                String.join("", Collections.nCopies(45, "―")) + " Estatísticas: " +
                String.join("", Collections.nCopies(46, "―")) + Colors.RESET + "\n\n");
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

    private static class ClientesQuantidade {
        private final Pair<String, Integer> par;

        private ClientesQuantidade(Pair<String, Integer> par) {
            this.par = par;
        }

        @Override
        public String toString() {
            return Colors.YELLOW +
                    "Cliente: " +
                    Colors.RESET +
                    par.getFirst() +
                    "\n" +
                    Colors.YELLOW +
                    "Distintos: " +
                    Colors.RESET +
                    par.getSecond().toString() +
                    "\n";
        }
    }

    private static class ProdutosQuantidade {
        private final Pair<String, Integer> par;

        private ProdutosQuantidade(Pair<String, Integer> par) {
            this.par = par;
        }

        @Override
        public String toString() {
            return Colors.YELLOW +
                    "Produto: " +
                    Colors.RESET +
                    par.getFirst() +
                    "\n" +
                    Colors.YELLOW +
                    "Distintos: " +
                    Colors.RESET +
                    par.getSecond().toString() +
                    "\n";
        }
    }

}
