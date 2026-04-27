import java.util.*;

class Process {
    int id;
    List<Integer> waitsFor = new ArrayList<>();

    Process(int id) {
        this.id = id;
    }
}

public class CMH_OR_Model {

    // returns true if a free path exists
    static boolean canEscape(int current, Process[] p, boolean[] visited) {

        if (visited[current]) return false;
        visited[current] = true;

        System.out.println("Visiting P" + current);

        // if no dependency → process is free
        if (p[current].waitsFor.isEmpty()) {
            return true;
        }

        // OR condition: ANY path can free the process
        for (int next : p[current].waitsFor) {
            if (canEscape(next, p, visited)) {
                return true;
            }
        }

        return false;
    }

    public static void main(String[] args) {

        int n = 4;
        Process[] p = new Process[n];

        for (int i = 0; i < n; i++)
            p[i] = new Process(i);

        /*
         Example:
         P0 waits for P1 or P2
         P1 waits for P3
         P2 waits for P3
         P3 has no dependency (free)
        */

        p[0].waitsFor.add(1);
        p[0].waitsFor.add(2);

        p[1].waitsFor.add(3);
        p[2].waitsFor.add(3);

        // P3 is free

        boolean[] visited = new boolean[n];

        System.out.println("Checking OR-model deadlock from P0\n");

        boolean result = canEscape(0, p, visited);

        if (result)
            System.out.println("\nNO DEADLOCK (escape path exists)");
        else
            System.out.println("\nDEADLOCK (no escape path)");
    }
}
