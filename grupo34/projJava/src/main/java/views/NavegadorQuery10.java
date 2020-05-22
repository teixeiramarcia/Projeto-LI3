package views;

import utils.Pair;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Collections;
import java.util.List;

public class NavegadorQuery10 {
    public static void printer(List<Pair<String, List<Double>>> catalogo, String titulo, String time) throws IOException {
        boolean flagCycle = true;
        int posicao_inicio = 0;
        int max_bound = catalogo.size();
        while (flagCycle) {
            System.out.print("\033\143");
            System.out.println(Colors.BLUE + titulo + Colors.RESET);
            System.out.println(time);

            printTablePosition(catalogo.get(posicao_inicio));

            System.out.println("\n");
            System.out.println(Colors.YELLOW + "Total de produtos com faturação: " + Colors.RESET + max_bound + "\n");
            System.out.print(Colors.YELLOW +
                    "1 -> " +
                    Colors.RESET +
                    "Produto Anterior.\n" +
                    Colors.YELLOW +
                    "2 -> " +
                    Colors.RESET +
                    "Produto Seguinte.\n" +
                    Colors.YELLOW +
                    "3 -> " +
                    Colors.RESET +
                    "Regressar ao menu inicial.\n\n" +
                    Colors.YELLOW +
                    "-> " +
                    Colors.RESET);
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String opcao = br.readLine();
            switch (opcao) {
                case "1":
                    if (posicao_inicio != 0) {
                        posicao_inicio--;
                    }
                    break;
                case "2":
                    if (posicao_inicio < max_bound) {
                        posicao_inicio++;
                    }
                    break;
                case "3":
                    flagCycle = false;
                    break;
                default:
                    break;
            }
        }
    }

    public static void printTablePosition(Pair<String, List<Double>> tabela_produto) {
        System.out.println(Colors.YELLOW + "Produto: " + Colors.RESET + tabela_produto.getFirst());
        System.out.println(Colors.BLUE);
        System.out.print(String.format("%14s", " |"));
        for (int mes = 0; mes < 12; mes++) {
            System.out.print(String.format("%14s", Meses.intToMes(mes) + " |"));
        }
        System.out.println(Colors.BLUE);
        System.out.println(String.join("", Collections.nCopies(190, "―")));
        System.out.print(Colors.RESET);
        for (int filial = 0; filial < 3; filial++) {
            System.out.print(String.format(Colors.YELLOW + "%12s |", "Filial " + (filial + 1)) + Colors.RESET);
            for (int mes = 0; mes < 12; mes++) {
                System.out.print(
                        String.format("%12.2f" + Colors.YELLOW + " |" + Colors.RESET,
                                tabela_produto.getSecond().get((filial * 12) + mes)));
            }
            System.out.println();
        }
    }
}
