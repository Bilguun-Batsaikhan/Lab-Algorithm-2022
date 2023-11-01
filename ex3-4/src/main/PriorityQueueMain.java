import java.util.*;

public class PriorityQueueMain {
    
    public static void main(String args[]) {
        Comparator<Integer> cmpInt = new Comparator<Integer>() {
            public int compare(Integer a, Integer b) {
                return a.compareTo(b);
            }
        };
        PriorityQueue<Integer> pq = new PriorityQueue<>(cmpInt);
        pq.push(3);
        pq.push(1);
        pq.push(4);
        pq.push(1);
        pq.push(5);
        pq.push(9);
        pq.push(2);
        pq.push(10);
        pq.push(7);
        pq.push(6);
        pq.push(11);
        pq.push(12);
        System.out.println(pq);

        System.out.println("\nPriorityQueue: \n");
        pq.printPQ();

        System.out.println("\nBy its priority order: \n");
        while (!pq.empty()) {
            System.out.print(pq.top() + " ");
            pq.pop();
        }
        System.out.println("\n");
    }
}
