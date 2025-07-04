public interface Coffee extends Cloneable {
    String getDescription();
    double getCost();
    Coffee clone();
}
