package views;

import controllers.IGestVendasController;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Input {
    private final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    private final IGestVendasController gestVendasController;

    public Input(IGestVendasController gestVendasController) {
        this.gestVendasController = gestVendasController;
    }

    int getInputMonth() {
        System.out.print(Colors.YELLOW +
                "Indique um mês (dígito entre 1 e 12): \n" +
                "Input -> " +
                Colors.RESET);
        int mes;
        while ((mes = getMonth()) == -1) {
            System.out.print(Colors.RED +
                    "Input inválido.\nIndique um dígito entre 1 e 12\n" +
                    "Input -->  " +
                    Colors.RESET);
        }
        return mes;
    }

    private int getMonth() {
        try {
            String input = br.readLine();
            int mes = Integer.parseInt(input);
            if (mes >= 1 && mes <= 12) {
                return mes - 1;
            }
        } catch (IOException | NumberFormatException e) {
            return -1;
        }
        return -1;
    }

    String getInputClient() {
        System.out.print(Colors.YELLOW +
                "Indique o cliente que pretende consultar: \n" +
                "Input -> " +
                Colors.RESET);
        String cliente;
        while ((cliente = getCliente()).equals("")) {
            System.out.print(Colors.RED +
                    "Input inválido.\nIndique um código de cliente válido (1 maiúscula e 4 dígitos) que exista no sistema\n" +
                    "Input -->  " +
                    Colors.RESET);
        }
        return cliente;
    }

    private String getCliente() {
        try {
            String input = br.readLine();
            if (gestVendasController.clienteValido(input) && gestVendasController.clienteExiste(input)) {
                return input;
            }
        } catch (IOException e) {
            return "";
        }
        return "";
    }

    int getInputInt() {
        System.out.print(Colors.YELLOW +
                "Indique o número de clientes dos quais pretende obter informação: \n" +
                "Input -> " +
                Colors.RESET);
        Integer n;
        while ((n = getInt()).equals(-1)) {
            System.out.print(Colors.RED +
                    "Input inválido.\nIndique um dígito\n" +
                    "Input -->  " +
                    Colors.RESET);
        }
        return n;
    }

    private Integer getInt() {
        try {
            return Integer.parseInt(br.readLine());
        } catch (IOException e) {
            return -1;
        }
    }

    String getInputProduct() {
        System.out.print(Colors.YELLOW +
                "Indique o produto que pretende consultar: \n" +
                "Input -> " +
                Colors.RESET);
        String cliente;
        while ((cliente = getProduto()).equals("")) {
            System.out.print(Colors.RED +
                    "Input inválido.\nIndique um código de produto válido (2 maiúsculas e 4 dígitos) que exista no sistema\n" +
                    "Input -->  " +
                    Colors.RESET);
        }
        return cliente;
    }

    private String getProduto() {
        try {
            String input = br.readLine();
            if (gestVendasController.produtoValido(input) && gestVendasController.produtoExiste(input)) {
                return input;
            }
        } catch (IOException e) {
            return "";
        }
        return "";
    }
}
