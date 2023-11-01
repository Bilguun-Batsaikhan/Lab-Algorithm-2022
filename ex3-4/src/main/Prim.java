import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.lang.Number;
import java.io.*;

public class Prim 
{
  static Collection<? extends AbstractEdge<String, Float>> edges;
    
    /*
     * MinimumSpanningForest find all the trees inside a graph thanks to the visit
     * then for each tree it calls the prim algorithm,
     * linking all the edges of each tree into a single list of edges
     */
    @SuppressWarnings("unchecked")
    public static  <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
        ArrayList<Node<V, L>> VColor = new ArrayList<>(); 
        ArrayList<Graph<V,L>> ListOfGraph = new ArrayList<>(); 
        List<Edge<V, L>> final_edges = new ArrayList<Edge<V,L>>();
        int count = 0;
        VColor = graph.initializeVertices();
            for(Node<V,L> nodo : VColor)
            {
                if(nodo.getColor().equals("White")) 
                    ListOfGraph.add(Visit(graph,VColor, nodo));
            }
            for(Graph<V,L> primGraph: ListOfGraph)
            {
                Collection<? extends AbstractEdge<V,L>> temporaney_edge;
                temporaney_edge = spanningTree(primGraph);   
                System.out.println("Tree n: " +count);
                count = count + 1;
                System.out.println((Float)getMinCost((List<AbstractEdge<V, L>>)temporaney_edge)); 
                System.out.println("\n");
                for(AbstractEdge<V,L> test: temporaney_edge)
                {
                    Edge<V, L> a = (Edge<V,L>)test;
                    final_edges.add(a);
                }
            }
        return final_edges;
    } 
    
    /*
     * Breadth visit of a graph
     * explores an array list of type node  
     * returns a graph containing all the black nodes found
     */
    public static <V, L extends Number> Graph<V,L> Visit(Graph<V,L> Main_graph, ArrayList<Node<V, L>> VColour, Node<V,L> Start) 
    {
        Graph<V,L> grafo = new Graph<>(false,true);
        ArrayList<Node<V,L>> GreyNode = new ArrayList<>();
        Start.setColor("Grey");

        GreyNode.add(Start); 
        grafo.addNode(Start.getValue());
        while(!GreyNode.isEmpty())
        {
            Node <V, L> Inspection_node = GreyNode.get(0);
            V valueOfNode = Inspection_node.getValue();
            ArrayList<V> adiacienti = (ArrayList<V>)Main_graph.getNeighbours(valueOfNode);
            for(V adjacent_node: adiacienti)
            {
                Node<V,L> node = null;
                for (Node<V, L> search_node : VColour) {
                    if (search_node.getValue().equals(adjacent_node)) {
                        node = search_node;
                        break;
                    }
                }
                if( node.getColor().equals("White"))
                {
                    node.setColor("Grey");
                    grafo.addNode(node.getValue());
                    L cost = Main_graph.getLabel(valueOfNode,node.getValue());
                    grafo.addEdge(valueOfNode, node.getValue(), cost);
                    GreyNode.add(node);
                }
                if(node.getColor().equals("Grey"))
                {
                    L cost = Main_graph.getLabel(valueOfNode,node.getValue());
                    grafo.addEdge(valueOfNode, node.getValue(), cost);
                }
               
            }
                Inspection_node.setColor("Black");
                GreyNode.remove(Inspection_node);
        }
        return grafo;
    } 
    /*
     * Prim alghoritm
     * returns a list of minimum weight edges to explore the entire graph passed as a parameter
     */
    @SuppressWarnings("unchecked")
    public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> spanningTree(Graph<V, L> graph) {
        ArrayList<Node<V, L>> vertices = new ArrayList<>();
        List<Edge<V, L>> edges = new ArrayList<>();
        vertices = graph.initializeVertices();
        Node<V, L> start = vertices.get(0);
        int zeroValue = 0;
        L zero = (L) Integer.valueOf(zeroValue);
        start.setCost(zero);
        start.setFather(null);

        Comparator<Node<V, L>> compCost = new Comparator<Node<V, L>>() {
            public int compare(Node<V, L> a, Node<V, L> b) {
                Number x = a.getCost();
                Number y = b.getCost();
  
                double costA = x.doubleValue();
                double costB = y.doubleValue();
                
                if (costA < costB) {
                    return -1;
                } else if (costA > costB) {
                    return 1;
                } else {
                    return 0;
                }
        }
        }; //COMPARATOR END
        PriorityQueue<Node<V, L>> Q = new PriorityQueue<>(compCost);
            for(Node<V, L> node: vertices) {
            Q.push(node);
        }

        while(!Q.empty()) {          
            Node<V, L> u = Q.top();       
            edges.add(new Edge<V,L>(u.getFather(), u.getValue(), u.getCost()));
            u.setVisited(true);
            Q.pop();                   
            V uValue = u.getValue();       

            ArrayList<V> adiacienti = (ArrayList<V>)graph.getNeighbours(uValue);
            List<Node<V, L>> nodeList = Q.getPriorityQ();

            for (V neighbour : adiacienti) {
                Node<V, L> neighbourNode = null;
                
                for (Node<V, L> node : nodeList) {
                    if (node.getValue().equals(neighbour)) {
                        neighbourNode = node;
                        break;
                    }
                }
                
                if (neighbourNode != null) {
                    if (Q.contains(neighbourNode)) {
                        L weight = graph.getLabel(uValue, neighbour);
                        int compare = compareCost(weight, neighbourNode.getCost());
                        if (compare < 0) {
                            if (!Q.remove(neighbourNode)) {
                                System.out.println("Couldn't remove the node");
                            }
                            neighbourNode.setCost(weight);
                            neighbourNode.setFather(uValue);
                            Q.push(neighbourNode);
                        }
                    }
                }
            }
        }   
        return edges;
    } 
    
    /*
     * Compare two type of L
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
     * sum all cost of a list of edge
     */
    @SuppressWarnings("unchecked")
    public static <V, L extends Number> L getMinCost(Collection<? extends AbstractEdge<V, L>> allEdges) {
        Float cost = 0.0f ;
        L result;
        for(AbstractEdge<V, L> edge: allEdges) {
            Edge<V, L> e = (Edge<V, L>)edge;
            if(e.getStart() != null) {
                Float c = e.getLabel().floatValue();
                cost += c;
            }
        }
        result = (L) Float.valueOf(cost);
        return result;
    }

    public static void main(String[] args) 
    {
        Graph<String,Float> grafo = new Graph<>(false,true);
      try{
        String line;
        FileReader file = new FileReader(args[0]);
        BufferedReader br = new BufferedReader (file);
        Scanner input = new Scanner ((Readable) file);
        while ((line = br.readLine ()) != null) {
            String[] dataRecords = line.split(",");
                String place1 = dataRecords[0];
                String place2 = dataRecords[1]; 
                Float cost =Float.valueOf(dataRecords[2]);
                cost = cost / 1000;
                grafo.addNode(place1);
                grafo.addNode(place2);
                grafo.addEdge(place1, place2, cost); 

      }
      input.close();
    }catch(IOException e) 
      { System.out.println("FILE COULD NOT BE READ"); }
      
      edges = minimumSpanningForest(grafo);
      System.out.println(edges.size());
      System.out.println("FINAL EDGES");
      Float numero = getMinCost(edges);
      System.out.println(numero + " km ");
    }
  }
