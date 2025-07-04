import java.util.*;

public class OrderHistory implements Iterable<Coffee> {
    private List<Coffee> orders = new ArrayList<>();

    public void addOrder(Coffee coffee) {
        orders.add(coffee);
    }

    @Override
    public Iterator<Coffee> iterator() {
        return orders.iterator();
    }
}
