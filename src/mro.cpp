#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Структура для представления многомерного прямоугольника
struct Rectangle {
    std::vector<double> min_coords; // Вектор минимальных координат
    std::vector<double> max_coords; // Вектор максимальных координат
};

// Функция для проверки пересечения двух прямоугольников
bool rectanglesOverlap(const Rectangle& a, const Rectangle& b, int n) {
    // Проверяем пересечение по каждому измерению
    for (int d = 0; d < n; ++d) {
        // Если максимальная координата одного прямоугольника меньше или равна минимальной другого,
        // или минимальная координата одного больше или равна максимальной другого, то они не пересекаются
        if (a.max_coords[d] <= b.min_coords[d] || a.min_coords[d] >= b.max_coords[d]) {
            return false; // Прямоугольники не пересекаются
        }
    }
    return true; // Прямоугольники пересекаются во всех измерениях
}

int main() {
    const double MAX_VAL = 1000.0; // Максимальное значение для координат
    const double MIN_SIZE = 10.0;   // Минимальный размер прямоугольника
    const double MAX_SIZE = 100.0;   // Максимальный размер прямоугольника
    int n, r;                        // Переменные для количества измерений и классов

    // Запрос у пользователя количества измерений и классов
    std::cout << "The number of dimensions: ";
    std::cin >> n;
    std::cout << "The number of classes: ";
    std::cin >> r;

    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    std::vector<Rectangle> rectangles; // Вектор для хранения сгенерированных прямоугольников

    // Генерация непересекающихся прямоугольников
    for (int i = 0; i < r; ++i) {
        Rectangle rect; // Создание нового прямоугольника
        bool overlaps;  // Флаг для проверки пересечения с другими прямоугольниками
        int attempts = 0; // Счетчик попыток генерации непересекающегося прямоугольника
        const int MAX_ATTEMPTS = 1000; // Максимальное количество попыток генерации

        do {
            rect.min_coords.clear(); // Очистка векторов координат перед новой генерацией
            rect.max_coords.clear(); // Очистка векторов координат перед новой генерацией
            for (int d = 0; d < n; ++d) {
                // Генерация минимальной координаты в диапазоне от 0 до MAX_VAL - MAX_SIZE
                double min_coord = (double)rand() / RAND_MAX * (MAX_VAL - MAX_SIZE);
                // Генерация случайного размера в пределах заданного диапазона
                double size = MIN_SIZE + (double)rand() / RAND_MAX * (MAX_SIZE - MIN_SIZE);
                double max_coord = min_coord + size; // Вычисление максимальной координаты

                // Добавление координат в векторы минимальных и максимальных значений
                rect.min_coords.push_back(min_coord);
                rect.max_coords.push_back(max_coord);
            }

            overlaps = false; // Сброс флага пересечения перед проверкой
            for (const auto& other : rectangles) {
                // Проверка на пересечение с уже существующими прямоугольниками
                if (rectanglesOverlap(rect, other, n)) {
                    overlaps = true; // Если есть пересечение, устанавливаем флаг в true
                    break;
                }
            }
            attempts++; // Увеличиваем счетчик попыток генерации
            
            // Если превышено максимальное количество попыток, выводим сообщение об ошибке и завершаем программу
            if (attempts > MAX_ATTEMPTS) {
                std::cerr << "Did not generate rectangles after " << MAX_ATTEMPTS << " attempts." << std::endl;
                return 1;
            }
        } while (overlaps); // Продолжаем генерировать пока есть пересечения

        rectangles.push_back(rect); // Добавляем успешно сгенерированный прямоугольник в вектор
    }

    std::ofstream outFile("vectors.txt"); // Открытие файла для записи данных о точках
    if (!outFile.is_open()) { 
        std::cerr << "Did not open file for writing." << std::endl;
        return 1; // Если файл не удалось открыть, выводим сообщение об ошибке и завершаем программу
    }

    // Генерация точек внутри прямоугольников и запись их в файл
    for (const auto& rect : rectangles) {
        int num_points = 10 + rand() % 100; // Генерация случайного количества точек от 10 до 100 для каждого прямоугольника
        for (int p = 0; p < num_points; ++p) {
            std::vector<double> point; // Вектор для хранения координат точки
            
            for (int d = 0; d < n; ++d) {
                // Генерация координаты точки внутри текущего прямоугольника
                double coord = rect.min_coords[d] + ((double)rand() / RAND_MAX) * (rect.max_coords[d] - rect.min_coords[d]);
                point.push_back(coord); // Добавление координаты точки в вектор точек
            }
            
            // Запись точки в файл, разделяя координаты пробелами
            for (int d = 0; d < n; ++d) {
                outFile << point[d];
                if (d < n - 1)
                    outFile << " "; // Добавляем пробел между координатами, кроме последней
            }
            outFile << std::endl; // Переход на новую строку после записи всех координат точки
        }
    }

    outFile.close(); // Закрытие файла после завершения записи данных
    std::cout << "Vectors have been successfully written into vectors.txt" << std::endl;

    return 0; // Завершение программы с кодом успеха
}
