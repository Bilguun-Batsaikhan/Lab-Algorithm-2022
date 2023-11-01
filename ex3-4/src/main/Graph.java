import java.util.ArrayList;
import java.util.Map;
import java.util.Objects;
import java.util.HashMap;
import java.util.AbstractCollection;

class Graph<V,L> implements AbstractGraph<V, L> {
    private boolean directed;
    private boolean labelled;
    private Map<V, HashMap<V, Edge<V,L>>> nodes = new HashMap<>();
    private ArrayList<Node<V, L>> vertices = new ArrayList<>();

   /*
    * compare two cost of type L
    */
    public static <L extends Number> int compareCost(L obj1, L obj2) {
        double value1 = obj1.doubleValue();
        double value2 = obj2.doubleValue();
    
        if (value1 < value2) {
            return -1;
        } else if (value1 > value2) {
            return 1;
        } else {
            return 0;
        }
    }
    /*  
     * initialize an array list with all vertex in the graph, used for prim alghoritm 
     */
    @SuppressWarnings("unchecked")
    public ArrayList<Node<V, L>> initializeVertices() {
        ArrayList<V> nodes = (ArrayList<V>)getNodes();
        for(V el: nodes) {
        int zeroValue = 0;
        L zero = (L) Integer.valueOf(zeroValue);
            vertices.add(new Node<V,L>(el, zero));
        }
        for(Node<V, L> node: vertices) {
            //node.setCost(node.getInfinity());
            node.setFather(null);
            node.setVisited(false);
            node.setCost(node.getInfinity());
        }
        return vertices;
    }

    public Graph(boolean directed, boolean labelled){
        this.directed = directed;
        this.labelled = labelled;
    }
    
    /*
     * return true if Edge is inside the graph
     * otherwise return false
     */
    public boolean containsEdge(V a, V b) {
        HashMap<V, Edge<V,L>> verticeA = nodes.get(a);

        if (verticeA == null || !verticeA.containsKey(b)) {
            return false;
        }
        if (directed) {
            return true;
        }
        HashMap<V, Edge<V,L>> verticeB = nodes.get(b);
        return verticeB != null && verticeB.containsKey(a);
    }

    /* 
     * check if the edge is present in the graph and if so remove it
     * if it is not direct we also delete the node for the other vertex
     */
    public boolean removeEdge(V a, V b) {
        if(a == null || b == null) {
            return false;
        }
        if(!containsEdge(a, b)) {
            return false;
        }
        HashMap<V, Edge<V,L>> verticeA = nodes.get(a);
        verticeA.remove(b);
        if(!directed) {
            HashMap<V, Edge<V,L>> verticeB = nodes.get(b);
            verticeB.remove(a);
        }
        return true;
    }
    
    /*
     * removes a node from the graph and all edges to which it is connected
     */
    public boolean removeNode(V a) {
        if(a == null) {
            return false;
        }
        if(!containsNode(a)) {
            return false;
        }
        
        for(Map.Entry<V, HashMap<V,Edge<V,L>>> entry : nodes.entrySet()) {
            Map<V,Edge<V,L>> edge = entry.getValue();
            if(containsNode(a)) {
                    edge.remove(a);
            }
        }
        nodes.remove(a);
        return true;
    }
    /*
     * add new node in the graph
     */
    public boolean addNode(V a) {
        if (a == null || containsNode(a)) {
            return false;
        }
        nodes.put(a, new HashMap<V, Edge<V,L>>());
        return true;
    }
    
    /*
     * add new edge between two nodes already present in the graph
     */
    public boolean addEdge(V a, V b, L l) {
        if(a == null || b == null) {
            return false;
        }
        if (labelled && l == null) {
            System.out.println("Label cannot be null in a labelled graph");
            return false;
        }
        HashMap<V, Edge<V,L>> verticeA = nodes.get(a);
        HashMap<V, Edge<V,L>> verticeB = nodes.get(b);
        if (verticeA == null || verticeB == null) {
            System.out.println("One of the nodes doesn't exist");
            return false;
        }
        if(containsEdge(a,b))
            return false;
        else
            verticeA.put(b, new Edge<V,L>(a, b, l));

        if (!directed) {
            if(!containsEdge(b,a))
                verticeB.put(a, new Edge<V,L>(b, a, l));
            else 
                return false;
        }
        return true;
    }
   /*
    * Getters and setters
    */
    public boolean isDirected() {
        return directed;
    }

    public boolean isLabelled() {
        return labelled;
    }

    /*
     * Control if the node is in graph
     */
    public boolean containsNode(V a) {
        return nodes.containsKey(a);
    }

    /*
     * Return size of graph
     */
    public int numNodes() {
        return nodes.size();
    }
    
    /*
     * Create an AbstracCollection which contains all node from graph
     */
    public AbstractCollection<V> getNodes() {
        return new ArrayList<V>(nodes.keySet());
    }
    /*
     * Crate an AbstracCollection which contains all edge from graph
     */
    public AbstractCollection<AbstractEdge<V,L>> getEdges() {
        ArrayList<AbstractEdge<V, L>> arcs = new ArrayList<>();
        for(HashMap<V, Edge<V, L>> nodes: nodes.values()) {
            for(Edge<V, L> arc: nodes.values()) {
                arcs.add(arc);
            }
        }
        return arcs;
    }
    /*
     * Create an AbstracCollection given a vertex which contains all neighbours 
     */
    public AbstractCollection<V> getNeighbours(V a) {
        return new ArrayList<V>(nodes.get(a).keySet());
    }
    /*
     * Recover the cost between two nodes 
     */
    public L getLabel(V a, V b) {
        if(!labelled || !containsEdge(a, b)) {
            return null;
        }
        HashMap<V, Edge<V, L>> verticeA = nodes.get(a);
        return verticeA.get(b).getLabel();
    }
     /*
      * Return number of edge of the graph
      */
    public int numEdges() {
        int count = 0;
        for(HashMap<V, Edge<V, L>> edges: nodes.values()) {
            count += edges.size();
        }
        if(!directed) {
            count = count/2;
        }
        return count;
    }
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Graph<?, ?> other = (Graph<?, ?>) obj;
        return Objects.equals(nodes, other.nodes)
                && Objects.equals(getEdges(), other.getEdges());
    }

    @Override
    public int hashCode() {
        return Objects.hash(nodes, getEdges());
    }
    public String toString() {
        StringBuilder sb = new StringBuilder();
        //! A, edges of A -> entry
        //! B, edges of B -> entry
        for(Map.Entry<V, HashMap<V,Edge<V,L>>> entry : nodes.entrySet())
        {
            //! A, edge of A -> arco
            Map<V,Edge<V,L>> arco = entry.getValue();
            sb.append("Vertice : "+ entry.getKey());
            for(Map.Entry<V, Edge<V,L>> archi : arco.entrySet())
            {
                Edge<V,L> edge = archi.getValue();
                sb.append("\nArco : " + archi.getKey() + " Peso: " + edge.getLabel());
            }
            sb.append("\n");

        }
        return sb.toString();
    }
}