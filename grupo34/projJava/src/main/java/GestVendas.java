import views.Manager;

import java.io.FileNotFoundException;

public class GestVendas {
    public static void main(String[] args) throws FileNotFoundException {
        Manager manager = new Manager(args[0]);
        manager.start();
    }
}
