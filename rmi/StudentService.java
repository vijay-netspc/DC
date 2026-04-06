import java.rmi.Remote;
import java.rmi.RemoteException;

public interface StudentService extends Remote {
    String getResult(String name, int marks) throws RemoteException;
}
