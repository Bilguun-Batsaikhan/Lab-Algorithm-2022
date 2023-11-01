import org.junit.*;
import java.util.Comparator;
import static org.junit.Assert.*;

public class PriorityQueueTest {
    Comparator<Integer> cmpInt = new Comparator<Integer>() {
        public int compare(Integer a, Integer b) {
            return a.compareTo(b);
        }
    };

    // Test if the priority queue is empty when initialized
    @Test
    public void testEmptyPriorityQueue() {
        PriorityQueue<Integer> pq = new PriorityQueue<>(cmpInt);
        assertTrue(pq.empty());
    }

    // Test if pushing elements to the queue increases its size
    @Test
    public void testpushingElements() {
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>(cmpInt);
        pq.push(3);
        assertEquals(1, pq.size());
        pq.push(5);
        assertEquals(2, pq.size());
    }

    // Test if peeking returns the highest priority element without removing it
    @Test
    public void testPeek() {
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>(cmpInt);
        pq.push(3);
        pq.push(5);
        assertEquals(3, (int) pq.top());
        assertEquals(2, pq.size());
    }

    // Test if removing elements from the queue decreases its size
    @Test
    public void testRemovingElements() {
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>(cmpInt);
        pq.push(3);
        pq.push(5);
        assertEquals(2, pq.size());
        pq.pop();
        assertEquals(1, pq.size());
        pq.pop();
        assertEquals(0, pq.size());
    }

    // Test if the queue is empty after removing all elements
    @Test
    public void testRemovingAllElements() {
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>(cmpInt);
        pq.push(3);
        pq.push(5);
        pq.push(7);
        pq.pop();
        pq.pop();
        pq.pop();
        assertTrue(pq.empty());
    }

    @Test
    public void testRemove() {
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>(cmpInt);
        pq.push(3);
        pq.push(5);
        pq.push(7);
        pq.remove(3);
        assertEquals(5, (int)pq.top());
    }

    @Test
    public void testRemoveWithContains() {
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>(cmpInt);
        pq.push(3);
        pq.push(5);
        pq.push(7);
        pq.remove(3);
        assertFalse(pq.contains(3));
    }

    @Test
    public void testRemoveWithSize() {
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>(cmpInt);
        pq.push(3);
        pq.push(5);
        pq.push(7);
        pq.remove(3);
        assertEquals(2, pq.size());
    }
}
