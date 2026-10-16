import java.time.LocalDateTime;
import java.util.*;

public class BaisanManagementSystem {

    public static class MenuItemEntity {
        private String name;
        private double price;

        public MenuItemEntity(String name, double price) {
            this.name = name;
            this.price = price;
        }

        public double getPrice() { return price; }
        public String getName() { return name; }
    }

    public static void main(String[] args) {
        System.out.println("[JAVA ENTERPRISE] Запуск системы Кафе «Байсан»...");

        MenuItemEntity plov = new MenuItemEntity("Плов Байсан", 2950.0);
        MenuItemEntity besh = new MenuItemEntity("Бесбармак Ханский", 4750.0);

        double subtotal = plov.getPrice() * 2 + besh.getPrice();
        double serviceFee = subtotal * 0.10; // 10% обслуживание
        double grandTotal = subtotal + serviceFee;

        System.out.println("\n=== ФИНАНСОВЫЙ ОТЧЕТ БЭКЕНДА (JAVA) ===");
        System.out.println("Время: " + LocalDateTime.now());
        System.out.println(" - 2x " + plov.getName() + " (" + (plov.getPrice()*2) + " ₸)");
        System.out.println(" - 1x " + besh.getName() + " (" + besh.getPrice() + " ₸)");
        System.out.println("----------------------------------------");
        System.out.printf("Сумма по меню:      %.2f ₸\n", subtotal);
        System.out.printf("Обслуживание (10%): %.2f ₸\n", serviceFee);
        System.out.printf("ИТОГО К РАСЧЕТУ:    %.2f ₸\n", grandTotal);
        System.out.println("Статус: ОПЛАЧЕНО УСПЕШНО");
        System.out.println("========================================\n");
    }
}