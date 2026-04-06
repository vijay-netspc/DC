import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try {
            Scanner sc = new Scanner(System.in);

            System.out.print("Enter student name: ");
            String name = sc.nextLine();

            System.out.print("Enter marks: ");
            int marks = sc.nextInt();

            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            StudentService service = (StudentService) registry.lookup("StudentResult");

            String result = service.getResult(name, marks);

            System.out.println("\n--- Result from Server ---");
            System.out.println(result);

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
