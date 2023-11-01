import java.util.ArrayList;

public class Node<V, L> {
    private ArrayList<Edge<V, L>> edges = new ArrayList<>();
    private V value;
    private V father = null;
    private boolean visited = false;
    private String color;
    private L cost; 

 /*
  * Supplemental class to facilitate updated distances of prim's algorithm and also to keep track of colors for visit 
  */
    public Node(V value, L c) {
        this.value = value;
        this.cost = c;
        this.color = "White";
    }
    /*    
     * Used of prim's algorithm to set distances to infinity
     * L extends Number, so use the constants provided by numeric classes
     * return null if L doesn't extend Number or no suitable representation of infinity is found
     */
    @SuppressWarnings("unchecked")
    public L getInfinity() {
            if (cost instanceof Integer) {
                return (L) Integer.valueOf(Integer.MAX_VALUE);
            } else if (cost instanceof Double) {
                return (L) Double.valueOf(Double.POSITIVE_INFINITY);
            } else if (cost instanceof Float) {
                return (L) Float.valueOf(Float.POSITIVE_INFINITY);
            } 
        return null; 
    }
    /*
     * Getters and Setters
     */
    public V getValue() {
        return value;
    }

    public void setValue(V value) {
        this.value = value;
    }

    public V getFather() {
        return father;
    }

    public void setFather(V father) {
        this.father = father;
    }

    public boolean isVisited() {
        return visited;
    }

    public void setVisited(boolean visited) {
        this.visited = visited;
    }

    public L getCost() {
        return cost;
    }

    public void setCost(L cost) {
        this.cost = cost;
    }
    
    public boolean addEdge(Edge<V, L> edge) {
        edges.add(edge);
        return true;
    }
    
    public ArrayList<Edge<V, L>> getEdges() {
        return edges;
    }
    @Override
    public String toString() {
        return value + " ";
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }
}
