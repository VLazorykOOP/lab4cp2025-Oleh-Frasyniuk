public class Main {
    public static void main(String[] args) {
        Coffee espresso = new Espresso();

        Coffee order1 = new MilkDecorator(espresso.clone());
        Coffee order2 = new MilkDecorator(new MilkDecorator(espresso.clone())); // Double milk

        OrderHistory history = new OrderHistory();
        history.addOrder(order1);
        history.addOrder(order2);

        for (Coffee coffee : history) {
            System.out.println(coffee.getDescription() + " - $" + coffee.getCost());
        }
    }
}
