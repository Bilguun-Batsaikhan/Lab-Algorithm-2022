
import java.util.*;
public class GraphMain {
   static Graph<String, Integer> grafo = new Graph<>(false,true);
   //static Graph<String, Integer>
    static ArrayList<Node<String, Integer>> nodes; //V
    static Comparator<Node<String, Integer>> cmpCost = new Comparator<Node<String, Integer>>() {
        public int compare(Node<String, Integer> a, Node<String, Integer> b) {
            Integer x = a.getCost();
            Integer y = b.getCost();
            return x.compareTo(y);
        }
    };
    static PriorityQueue<Node<String, Integer>> pq = new PriorityQueue<>(cmpCost);
    public static void main(String[] args) {
        /* 
        pq.push(new Node<String,Integer>("a"));
        pq.push(new Node<String,Integer>("b"));
        pq.push(new Node<String,Integer>("c"));
        pq.push(new Node<String,Integer>("d"));
        pq.push(new Node<String,Integer>("e"));
        pq.push(new Node<String,Integer>("f"));
        pq.push(new Node<String,Integer>("g"));
        System.out.println(pq);
        HashMap<Node<String, Integer>, Integer> indexOfNodes = pq.getElemIndex();
        Integer index = indexOfNodes.get(new Node<String, Integer>("b"));
        List<Node<String, Integer>> nodeList = pq.getPriorityQ();
        Node<String, Integer> node = nodeList.get(index);
        System.out.println(node);
        */
        /* 
        grafo.addNode("a");
        grafo.addNode("b");
        grafo.addNode("c");
        grafo.addNode("d");
        grafo.addNode("e");
        grafo.addNode("f");
        grafo.addNode("g");
        
        grafo.addEdge("a", "f", 2);
        grafo.addEdge("a", "b", 2);
        grafo.addEdge("f", "b", 5);
        grafo.addEdge("f", "c", 4);
        grafo.addEdge("c", "b", 1);
        grafo.addEdge("c", "e", 4);
        grafo.addEdge("e", "b", 3);
        grafo.addEdge("a", "d", 7);
        grafo.addEdge("d", "b", 4);
        grafo.addEdge("e", "d", 1);
        grafo.addEdge("d", "g", 5);
        grafo.addEdge("e", "g", 7);
        */
        grafo.addNode("a");
        grafo.addNode("b");
        grafo.addNode("c");

        grafo.addEdge("a", "b", 2);
        grafo.addEdge("b", "c", 1);
        //grafo.removeNode("b");
        //grafo.removeEdge("a", "b");
        //int numNodes = grafo.numNodes();
        //int numEdges = grafo.numEdges();
        //System.out.println("Number of nodes: " + numNodes);
        //System.out.println("Number of edges: " + numEdges);
        //System.out.println("Weight of (a,d): " + grafo.getLabel("a", "d"));
        //System.out.println(grafo);
        //System.out.println(grafo.getNodes());
        //System.out.println(grafo.getEdges());
        
        /*ArrayList<Node<String, Integer>> nodes = grafo.MST_PRIM(
            start, new ArrayList<Node<String, Integer>>(), cmpCost);
        System.out.println("Nodes after Prim");
        for(Node<String, Integer> node: nodes) {
            System.out.println(node);
        }*/
    }
}
