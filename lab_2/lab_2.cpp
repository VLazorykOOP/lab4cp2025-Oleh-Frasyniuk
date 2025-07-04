#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <mutex>

struct Car {
    int id;
    std::atomic<int> x_pos;

    Car(int id_, int start_pos) : id(id_), x_pos(start_pos) {}

    Car(const Car& other) : id(other.id), x_pos(other.x_pos.load()) {}
    Car& operator=(const Car& other) {
        if (this != &other) {
            id = other.id;
            x_pos.store(other.x_pos.load());
        }
        return *this;
    }

    Car(Car&& other) noexcept : id(other.id), x_pos(other.x_pos.load()) {}
    Car& operator=(Car&& other) noexcept {
        if (this != &other) {
            id = other.id;
            x_pos.store(other.x_pos.load());
        }
        return *this;
    }
};

struct Motorcycle {
    int id;
    std::atomic<int> y_pos;

    Motorcycle(int id_, int start_pos) : id(id_), y_pos(start_pos) {}

    Motorcycle(const Motorcycle& other) : id(other.id), y_pos(other.y_pos.load()) {}
    Motorcycle& operator=(const Motorcycle& other) {
        if (this != &other) {
            id = other.id;
            y_pos.store(other.y_pos.load());
        }
        return *this;
    }

    Motorcycle(Motorcycle&& other) noexcept : id(other.id), y_pos(other.y_pos.load()) {}
    Motorcycle& operator=(Motorcycle&& other) noexcept {
        if (this != &other) {
            id = other.id;
            y_pos.store(other.y_pos.load());
        }
        return *this;
    }
};

// Розмір області симуляції
constexpr int SIMULATION_SIZE = 100;

// Швидкість руху (крок за ітерацію)
constexpr int V = 1;

// Затримка між оновленнями (мс)
constexpr int UPDATE_DELAY_MS = 100;

std::mutex cout_mutex;


void move_cars(std::vector<Car>& cars) {
    while (true) {
        for (auto& car : cars) {
            int old_x = car.x_pos.load();
            int new_x = old_x + V;
            if (new_x > SIMULATION_SIZE) new_x = 0; // Зациклення
            car.x_pos.store(new_x);

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Car " << car.id << " at X=" << new_x << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_DELAY_MS));
    }
}

void move_motorcycles(std::vector<Motorcycle>& motorcycles) {
    while (true) {
        for (auto& moto : motorcycles) {
            int old_y = moto.y_pos.load();
            int new_y = old_y + V;
            if (new_y > SIMULATION_SIZE) new_y = 0; // Зациклення
            moto.y_pos.store(new_y);

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Motorcycle " << moto.id << " at Y=" << new_y << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_DELAY_MS));
    }
}

int main() {
    std::vector<Car> cars;
cars.emplace_back(1, 0);
cars.emplace_back(2, 10);
cars.emplace_back(3, 20);

std::vector<Motorcycle> motorcycles;
motorcycles.emplace_back(1, 0);
motorcycles.emplace_back(2, 15);
motorcycles.emplace_back(3, 30);


    // Запускаємо два потоки: один для автомобілів, інший для мотоциклів
    std::thread car_thread(move_cars, std::ref(cars));
    std::thread moto_thread(move_motorcycles, std::ref(motorcycles));
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // Чекаємо, щоб потоки працювали (у цьому прикладі вічно)
    car_thread.join();
    moto_thread.join();

    return 0;
}
