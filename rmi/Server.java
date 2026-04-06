import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Server {
    public static void main(String[] args) {
        try {
            StudentService service = new StudentServiceImpl();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("StudentResult", service);
            System.out.println("Student Result Server is running...");
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
