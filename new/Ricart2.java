import java.util.*;

class Process {
    int id;
    int reqtime;
    int replies = 0;
    boolean requesting = false;

    List<Integer> deferred = new ArrayList<>();

    Process(int id) {
        this.id = id;
    }

    // Now timestamp is given by user
    void requestCS(int time) {
        requesting = true;
        reqtime = time;
        System.out.println("Process " + id + " requesting CS at time " + reqtime);
    }

    boolean shouldReply(Process sender) {

        if (!requesting) return true;

        if (sender.reqtime < this.reqtime) return true;

        if (sender.reqtime == this.reqtime && sender.id < this.id) return true;

        return false;
    }

    void receiveRequest(Process sender) {
        if (shouldReply(sender)) {
            System.out.println("Process " + this.id + " REPLY to Process " + sender.id);
            sender.receiveReply();
        } else {
            System.out.println("Process " + this.id + " DEFER reply to Process " + sender.id);
            deferred.add(sender.id);
        }
    }

    void receiveReply() {
        replies++;
    }

    void tryEnterCS(int n) {
        if (requesting && replies == n - 1) {
            enterCS(n);
        }
    }

    void enterCS(int n) {
        System.out.println("Process " + id + " ENTERS CS");
        exitCS(n);
    }

    void exitCS(int n) {
        System.out.println("Process " + id + " EXITS CS");

        requesting = false;
        replies = 0;

        for (int pid : deferred) {
            System.out.println("Process " + id + " sends deferred REPLY to Process " + pid);
            Main.process[pid].receiveReply();
        }

        deferred.clear();
        System.out.println();
    }
}

public class Ricart2 {

    static Process[] process;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of processes: ");
        int n = sc.nextInt();

        process = new Process[n];

        for (int i = 0; i < n; i++) {
            process[i] = new Process(i);
        }

        System.out.print("Enter number of requests: ");
        int r = sc.nextInt();

        // INPUT: process id + timestamp
        for (int i = 0; i < r; i++) {
            System.out.print("Enter process id and timestamp: ");
            int pid = sc.nextInt();
            int time = sc.nextInt();

            process[pid].requestCS(time);
        }

        System.out.println("\n--- Processing Requests ---");

        for (Process p1 : process) {
            if (p1.requesting) {
                for (Process p2 : process) {
                    if (p1.id != p2.id) {
                        p2.receiveRequest(p1);
                    }
                }
            }
        }

        System.out.println("\n--- Checking CS Entry ---");

        for (Process p : process) {
            p.tryEnterCS(n);
        }

        System.out.println("\n--- Rechecking after deferred replies ---");

        for (Process p : process) {
            p.tryEnterCS(n);
        }
    }
}
