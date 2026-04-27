import java.util.*;

class Process {
    int id;
    List<Integer> waitsFor = new ArrayList<>();

    Process(int id) {
        this.id = id;
    }
}

public class CMH_MultiWait {

    static boolean detect(int start, int current, Process[] p, Set<String> visited) {

        if (!visited.add(start + "-" + current)) {
            return false;
        }

        System.out.println("PROBE(" + start + "," + current + ")");

        for (int next : p[current].waitsFor) {

            // cycle found
            if (next == start) {
                System.out.println("Deadlock detected at P" + start);
                return true;
            }

            // forward probe
            if (detect(start, next, p, visited)) {
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
         Example deadlock:
         P0 → P1, P2
         P1 → P3
         P2 → P3
         P3 → P0  (cycle)
        */

        p[0].waitsFor.add(1);
        p[0].waitsFor.add(2);

        p[1].waitsFor.add(3);

        p[2].waitsFor.add(3);

        p[3].waitsFor.add(0);

        System.out.println("Deadlock detection started from P0\n");

        boolean result = detect(0, 0, p, new HashSet<>());

        if (!result)
            System.out.println("No deadlock detected");
    }
}
