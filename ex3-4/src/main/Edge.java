import java.util.Objects;

public class Edge<V, L> implements AbstractEdge<V, L> {
    private V start;
    private V end;
    private L label;

    public Edge(V a, V b, L label) {
        this.start = a;
        this.end = b;
        this.label = label;
    }

    public V getStart() {
        return start;
    }

    public void setStart(V start) {
        this.start = start;
    }

    public V getEnd() {
        return end;
    }

    public void setEnd(V end) {
        this.end = end;
    }

    public L getLabel() {
        return label;
    }

    public void setlabel(L label) {
        this.label = label;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Edge<?, ?> other = (Edge<?, ?>) obj;
        return Objects.equals(start, other.start)
                && Objects.equals(end, other.end)
                && Objects.equals(label, other.label);
    }

    @Override
    public int hashCode() {
    return Objects.hash(start, end, label);
    }

    public String toString() {
        return "[" + start + "," + end + "," + label + "]";
    }
}
