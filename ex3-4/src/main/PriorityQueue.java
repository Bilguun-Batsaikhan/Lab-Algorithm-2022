import java.util.*;

public class PriorityQueue<E> implements AbstractQueue<E>{
    private List<E> priorityQ = new ArrayList<E>();
    private Comparator<E> comparator;
    private int size = 0; 
    private HashMap<E, Integer> elemIndex = new HashMap<>();
    
    /*
     * Returns the list of elements in the Priority Queue
     */ 
    public List<E> getPriorityQ() {
        return priorityQ;
    }
    
    /* 
     * Returns the index of element in the Hash map of one element
    */ 
    public HashMap<E, Integer> getElemIndex() {
        return elemIndex;
    }

    public PriorityQueue(Comparator<E> comparator) {
        this.comparator = comparator;
    }    
    
    public void printPQ() {
        System.out.println(priorityQ);
    }
    /*
     * Return the father's index
     */ 
    public int Parent(int i) {
        if(i == 0) return 0;
        return (i - 1) / 2;
    }

    /*
     * Left child index
     */ 
    public int Left(int i) {
    if(2 * i + 1 < size) {
        return 2 * i + 1;
    } 
    return i;
    }

    /*
     * Right child index
     */
    public int Right(int i) {
    if(2 * i + 2 < size) {
        return 2 * i + 2;
    }
    return i;
    }
    
    /* 
     * Check if the priority queue is empty
     */
     public boolean empty() {
        return size <= 0;
    }
    /*
     * Returns the element at the top of the Priority Queue
     */
     public E top() {
        if(empty()) {
            throw new NoSuchElementException();
        }
        return priorityQ.get(0);
    }
    
    /*
     * Delete the top elem, swap with the last elem in priority queue and call heapify to fix the heap
     */
     public void pop() {
        if(empty()) {
            throw new NoSuchElementException();
        }
        E lastElem = priorityQ.get(size - 1);
        E elemToPop = priorityQ.get(0);
        priorityQ.set(0, lastElem); 
        priorityQ.remove(size - 1);
        elemIndex.remove(elemToPop);
        if(size > 1)
        elemIndex.put(priorityQ.get(0), 0);
        size--;
        if(size > 0)
        heapify(0);
    }
    
    /** 
     * delete one elem in any position, swap with the last elem in priority queue, 
     * call heapify to adjust the heap down and then check up if the element is in the right position
     * */
    public boolean remove(E e) {
        if (!elemIndex.containsKey(e)) {
            return false;
        }
        int index = elemIndex.get(e);
        swap(index, size - 1);
        priorityQ.remove(size - 1);
        size--;
        elemIndex.remove(e);
        if (index < size) {
            heapify(index);
            while (index > 0) {
                int parentIndex = Parent(index);
                if (comparator.compare(priorityQ.get(parentIndex), priorityQ.get(index)) <= 0) {
                    break;
                }
                swap(parentIndex, index);
                index = parentIndex;
            }
        }
        return true;
    }
    
    /*
     * Control if an elem is contains in the priority queue, through the hashmap
     */
     public boolean contains(E e) {
        return elemIndex.containsKey(e);
    }

    /*
     * Heapify fix the heap after doing a pop or remove, by swap elem in wrong pisition 
     * compared with the help of the comparator.
     * After heapify,the priority queue is a minimum heap again
     */
    public void heapify(int i) {
        int leftChildIndex = Left(i);
        int rightChildIndex = Right(i);
        int smallest = i;
        if (leftChildIndex < size && comparator.compare(priorityQ.get(leftChildIndex), priorityQ.get(smallest)) < 0) {
            smallest = leftChildIndex;
        }
        if (rightChildIndex < size && comparator.compare(priorityQ.get(rightChildIndex), priorityQ.get(smallest)) < 0) {
            smallest = rightChildIndex;
        }
        if (smallest != i) {
            swap(smallest, i);
            heapify(smallest);
        }
    }    
    /**  
     * Push inserts a new elem in the last position of priority queue 
     * then it compares with the father to check if it is in the correct position, 
     * if it is not, swaps are made until it is in the correct position
    */
    public boolean push(E e) {
        if(contains(e)) {
            return false;
        }
        ++size;
        priorityQ.add(e);
        int p = size - 1;
        int parentIndex = Parent(p);
        elemIndex.put(e, p);

        while(p > 0 && comparator.compare(priorityQ.get(p) , priorityQ.get(parentIndex)) < 0) {
            swap(p, parentIndex);
            p = parentIndex;
            parentIndex = Parent(p);
        }
        return true;
    }
    /* 
     * This function is used to swap elements in the priority queue and update the index in the hash map. 
     * i child, j father
     */
     public boolean swap(int i, int j) {
        E temp1 = priorityQ.get(i); 
        E temp2 = priorityQ.get(j); 
        priorityQ.set(i, priorityQ.get(j));
        priorityQ.set(j, temp1);
        elemIndex.put(temp1, j);
        elemIndex.put(temp2, i);
        return true;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        int level = 0;
        int count = 0;
        int nextCount = 1;
        sb.append("PriorityQueue:\n");
        for (int i = 0; i < size; i++) {
            if (count == 0) {
                count = nextCount;
                nextCount = 0;
                level++;
                sb.append("\nLevel " + level + ": ");
            }
            E element = priorityQ.get(i);
            sb.append(element + " ");
            if (element != null) {
                nextCount += 2;
            }
            count--;
        }
        return sb.toString();
    }

    public int size() {
        return this.size;
    }
}