import static org.junit.Assert.*;
import org.junit.*;
import java.util.ArrayList;
import java.util.Collection;

public class GraphTest 
{
   
    @Test
    public void testGraphLabelled() {
        Graph<String,Double> g = new Graph<>(false, true);
        assertTrue(g.isLabelled());
    }
    
    @Test
    public void testGraphDirected() {
        Graph<String,Double> g = new Graph<>(true, true);
        assertTrue(g.isDirected());
    }

    @Test
    public void testGraphAddNode() {
        Graph<String,Double> g = new Graph<>(true, false);
        g.addNode("a");
        assertTrue(g.containsNode("a"));
    }

    @Test
    public void testGraphAddEdgeDirected() {
        Graph<String,Double> g = new Graph<>(true, false);
        g.addNode("a");
        g.addNode("b");
        g.addEdge("a","b", 2.0);
        assertTrue(g.containsEdge("a","b"));
    }
    
    @Test
    public void testGraphAddEdgeNotDirected() {
        Graph<String,Double> g = new Graph<>(false, false);
        g.addNode("a");
        g.addNode("b");
        g.addEdge("a","b", 2.0);
        assertTrue(g.containsEdge("b","a"));
    }
    
    @Test
    public void testGraphContNode(){
        Graph<String,Double> g = new Graph<>(false, false);
        g.addNode("x");
        assertEquals(1, g.numNodes());
    }

    @Test
    public void testGraphContEdgeDirected(){
        Graph<String, Double> g = new Graph<>(true, false);
        g.addNode("x");
        g.addNode("y");
        g.addEdge("x", "y", 0.0);
        assertEquals(1, g.numEdges());
    }

    @Test
    public void testGraphContEdgeNotDirected(){
        Graph<String, Double> g = new Graph<>(false, false);
        g.addNode("x");
        g.addNode("y");
        g.addEdge("x", "y", 0.0);
        assertEquals(1, g.numEdges());
    }
    @Test
    public void testGraphRemoveNode(){
        Graph<String, Double> g = new Graph<>(false, false);
        g.addNode("x");
        g.removeNode("x");
        assertEquals(0, g.numNodes());
    }
    @Test
    public void testGraphRemoveEdge(){
        Graph<String, Double> g = new Graph<>(false, false);
        g.addNode("x");
        g.addNode("y");
        g.addEdge("x", "y", 0.0);
        g.removeEdge("x", "y");
        assertEquals(0, g.numEdges());
    }

    @Test
    public void testGraphGetLabel(){
        Graph<String, Double> g = new Graph<>(false, true);
        g.addNode("x");
        g.addNode("y");
        g.addEdge("x", "y", 2.2);
        double x = (double)g.getLabel("x","y");
        assertEquals(2,2, x);
    }
    
    @Test
    public void testGraphNeighbour()
    {
        Graph<String, Double> g = new Graph<>(false, true);
        g.addNode("x");
        g.addNode("y");
        g.addNode("z");
        g.addEdge("x", "y", 2.2);
        g.addEdge("x", "z", 3.2);
        Collection<String> Real_vicini = g.getNeighbours("x");
        Collection<String> Expeted_vicini = new ArrayList<>();
        Expeted_vicini.add("y");
        Expeted_vicini.add("z");
        assertEquals(Expeted_vicini, Real_vicini);
    }

    @Test
    public void testGraphGetNodes()
    {
        Graph<String, Double> g = new Graph<>(false, true);
        g.addNode("x");
        g.addNode("y");
        g.addNode("z");
        Collection<String> Real_node = g.getNodes();
        Collection<String> Expeted_node = new ArrayList<>();
        Expeted_node.add("x");
        Expeted_node.add("y");
        Expeted_node.add("z");
        assertEquals(Expeted_node, Real_node);
    }

    @Test
    public void testGraphGetEdge()
    {
        Graph<String, Double> g = new Graph<>(true, true);
        g.addNode("x");
        g.addNode("y");
        g.addNode("z");
        g.addEdge("x", "y", 0.0);
        g.addEdge("x", "z", 0.0);
        Collection<AbstractEdge<String,Double>> Real_node = g.getEdges();
        Collection<AbstractEdge<String,Double>> Expeted_node = new ArrayList<>();
        Edge<String,Double> T = new Edge<String,Double>("x", "y", 0.0);
        Edge<String,Double> L = new Edge<String,Double>("x", "z", 0.0);
        Expeted_node.add(T);
        Expeted_node.add(L);
        assertEquals(Expeted_node, Real_node);
    }
    
    @Test
    public void testPrim()
    {
        Graph<String, Float> g = new Graph<>(false,true);
        g.addNode("a");
        g.addNode("b");
        g.addNode("c");
        g.addNode("d");
        g.addNode("e");
        g.addNode("f");
        g.addNode("g");
        
        g.addEdge("a", "f", 2.0f);
        g.addEdge("a", "b", 2.0f);
        g.addEdge("f", "b", 5.0f);
        g.addEdge("f", "c", 4.0f);
        g.addEdge("c", "b", 1.0f);
        g.addEdge("c", "e", 4.0f);
        g.addEdge("e", "b", 3.0f);
        g.addEdge("a", "d", 7.0f);
        g.addEdge("d", "b", 4.0f);
        g.addEdge("e", "d", 1.0f);
        g.addEdge("d", "g", 5.0f);
        g.addEdge("e", "g", 7.0f);

        Collection<? extends AbstractEdge<String, Float>> edges;
        edges = Prim.spanningTree(g);
        Float cont = (Float) Prim.getMinCost(edges);
        Float expetd = 14.0f;
        assertEquals(expetd, cont);
    }

    @Test
    public void testVisit()
    {
        Graph<String, Float> g = new Graph<>(false,true);
        g.addNode("a");
        g.addNode("b");
        g.addNode("c");
        g.addNode("d");
        g.addNode("e");
        g.addNode("f");
        g.addNode("g");
        
        g.addEdge("a", "f", 2.0f);
        g.addEdge("a", "b", 2.0f);
        g.addEdge("f", "b", 5.0f);
        g.addEdge("f", "c", 4.0f);
        g.addEdge("c", "b", 1.0f);
        g.addEdge("c", "e", 4.0f);
        g.addEdge("e", "b", 3.0f);
        g.addEdge("a", "d", 7.0f);
        g.addEdge("d", "b", 4.0f);
        g.addEdge("e", "d", 1.0f);
        g.addEdge("d", "g", 5.0f);
        g.addEdge("e", "g", 7.0f);
        ArrayList<Node<String, Float>> VColor = new ArrayList<>();
        VColor = g.initializeVertices();
        Graph<String, Float> after_visit;
        after_visit = Prim.Visit(g,VColor, VColor.get(0));
        assertEquals(g, after_visit);
    }
    
    @Test
    public void testMinimumSpanningForest()
    {
        Graph<String, Float> g = new Graph<>(false,true);
        g.addNode("a");
        g.addNode("b");
        g.addNode("c");
        g.addNode("d");
        g.addNode("e");
        g.addNode("f");
        g.addNode("g");
        g.addNode("x");
        g.addNode("y");
        g.addNode("z");
        
        g.addEdge("a", "f", 2.0f);
        g.addEdge("a", "b", 2.0f);
        g.addEdge("f", "b", 5.0f);
        g.addEdge("f", "c", 4.0f);
        g.addEdge("c", "b", 1.0f);
        g.addEdge("c", "e", 4.0f);
        g.addEdge("e", "b", 3.0f);
        g.addEdge("a", "d", 7.0f);
        g.addEdge("d", "b", 4.0f);
        g.addEdge("e", "d", 1.0f);
        g.addEdge("d", "g", 5.0f);
        g.addEdge("e", "g", 7.0f);
        g.addEdge("x", "y", 5.0f);
        g.addEdge("x", "z", 5.0f);

        Collection<? extends AbstractEdge<String, Float>> edges;
        edges = Prim.minimumSpanningForest(g);
        Float cont = (Float) Prim.getMinCost(edges);
        Float expetd = 24.0f;
        assertEquals(expetd, cont);
    }
}

