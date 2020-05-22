package views;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;


public class Navegador {
    public static <T> void printer(List<T> catalogo, String titulo, String time) throws IOException {
        boolean flagCycle = true;
        int posicao_inicio = 0;
        int max_bound = catalogo.size();
        while (flagCycle) {
            System.out.print("\033\143");
            System.out.println(Colors.BLUE + titulo + Colors.RESET);
            System.out.println(time +
                    Colors.YELLOW +
                    "A mostrar resultados de " +
                    posicao_inicio +
                    " até " +
                    (posicao_inicio + 10) +
                    ":\n" +
                    Colors.RESET);
            for (int i = posicao_inicio; i < posicao_inicio + 10 && i < max_bound; i++) {
                System.out.println(catalogo.get(i));
            }
            System.out.println("\n");
            System.out.println(Colors.YELLOW + "Total: " + Colors.RESET + max_bound + "\n");
            System.out.print(Colors.YELLOW +
                    "1 -> " +
                    Colors.RESET +
                    "10 resultados anteriores.\n" +
                    Colors.YELLOW +
                    "2 -> " +
                    Colors.RESET +
                    "10 resultados seguintes.\n" +
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
                        posicao_inicio -= 10;
                    }
                    break;
                case "2":
                    if (posicao_inicio + 10 < max_bound) {
                        posicao_inicio += 10;
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
}
