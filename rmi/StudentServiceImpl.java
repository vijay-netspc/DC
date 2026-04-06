import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;

public class StudentServiceImpl extends UnicastRemoteObject implements StudentService {

    protected StudentServiceImpl() throws RemoteException {
        super();
    }

    public String getResult(String name, int marks) throws RemoteException {
        String grade;

        if (marks >= 90) grade = "A";
        else if (marks >= 75) grade = "B";
        else if (marks >= 60) grade = "C";
        else if (marks >= 50) grade = "D";
        else grade = "Fail";

        return "Student: " + name +
               "\nMarks: " + marks +
               "\nGrade: " + grade;
    }
}
