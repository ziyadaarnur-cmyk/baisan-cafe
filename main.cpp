#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>

using namespace std;
mutex mtx;

struct DishItem {
    int id;
    string name;
    double price;
};

struct OrderTask {
    int orderId;
    int tableNumber;
    vector<pair<DishItem, int>> items;
};

class CafeBaisanConsoleEngine {
private:
    map<int, DishItem> globalMenu = {
        {108, {108, "Завтрак Байсан", 2850.0}},
        {605, {605, "Рибай стейк", 5850.0}},
        {901, {901, "Плов Байсан", 2950.0}},
        {907, {907, "Бесбармак Ханский", 4750.0}}
    };
    queue<OrderTask> kitchenQueue;

public:
    void renderInteriorBlueprint() {
        cout << "\n=========================================================\n";
        cout << "   КАФЕ «БАЙСАН» (АСТАНА) — ЯДРО КУХНИ C++                \n";
        cout << "   Слоган: Дәмді ас • Жақсы көңіл-күй                    \n";
        cout << "=========================================================\n";
        cout << "[ ПАНОРАМНОЕ ОКНО С ВИДОМ НА ГОРИЗОНТ И СОЛНЦЕ ]         \n";
        cout << "+-------------------------------------------------------+\n";
        cout << "| [Стол №1: Свободен]   [Стол №2: Занят]   [Бар: Активен]|\n";
        cout << "| [Стол №3: Занят]    * [Стол №4: VIP Заказ] [Терраса]  |\n";
        cout << "+-------------------------------------------------------+\n";
        cout << " Статус: ВСЕ СИСТЕМЫ УПРАВЛЕНИ И ПОТОКИ АКТИВНЫ          \n";
        cout << "=========================================================\n\n";
    }

    void submitOrder(int orderId, int tableNum, vector<pair<int, int>> orderItems) {
        lock_guard<mutex> lock(mtx);
        OrderTask task;
        task.orderId = orderId;
        task.tableNumber = tableNum;
        for (auto& p : orderItems) {
            if (globalMenu.find(p.first) != globalMenu.end()) {
                task.items.push_back({globalMenu[p.first], p.second});
            }
        }
        kitchenQueue.push(task);
        cout << "[C++ KITCHEN] Заказ #" << orderId << " со столика №" << tableNum << " принят в обработку!\n";
    }

    void processKitchenQueue() {
        while (!kitchenQueue.empty()) {
            OrderTask currentTask;
            {
                lock_guard<mutex> lock(mtx);
                currentTask = kitchenQueue.front();
                kitchenQueue.pop();
            }

            cout << "\n--- ПРИГОТОВЛЕНИЕ ЗАКАЗА #" << currentTask.orderId << " (Стол №" << currentTask.tableNumber << ") ---\n";
            double subtotal = 0.0;
            for (auto& itemPair : currentTask.items) {
                DishItem d = itemPair.first;
                int qty = itemPair.second;
                subtotal += d.price * qty;
                cout << " > Готовится: " << qty << "x " << d.name << "\n";
                this_thread::sleep_for(chrono::milliseconds(100));
            }

            double serviceFee = subtotal * 0.10;
            double grandTotal = subtotal + serviceFee;

            cout << "---------------------------------------------------------\n";
            cout << " ФИСКАЛЬНЫЙ ОТЧЕТ (C++):\n";
            cout << " Сумма блюд:       " << fixed << setprecision(2) << subtotal << " ₸\n";
            cout << " Обслуживание 10%: " << serviceFee << " ₸\n";
            cout << " ИТОГО К ОПЛАТЕ:   " << grandTotal << " ₸\n";
            cout << "=========================================================\n";
        }
    }
};

int main() {
    CafeBaisanConsoleEngine engine;
    engine.renderInteriorBlueprint();
    engine.submitOrder(101, 4, {{108, 2}, {901, 1}});
    
    thread worker(&CafeBaisanConsoleEngine::processKitchenQueue, &engine);
    worker.join();
    return 0;
}
