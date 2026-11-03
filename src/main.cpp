#include <iostream>
#include <string>
#include "../include/Collection.hpp"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/Patient.h"

int main() {
    std::cout << "====================================================================\n";
    std::cout << " 1. ТЕСТИРОВАНИЕ Collection<T> С БАЗОВЫМИ ТИПАМИ (int)\n";
    std::cout << "====================================================================\n";

    Collection<int> numbers;
    numbers.add(10);
    numbers.add(45);
    numbers.add(80);
    numbers.add(15);
    numbers.add(99);

    std::cout << "Коллекция чисел (размер: " << numbers.get_size() << "):\n" << numbers;

    // Шаблонный поиск по предикату
    int idx = find_if(numbers, [](int x) { return x > 50; });
    std::cout << "Первый элемент > 50 найден на позиции [" << idx << "]: " << numbers[idx] << "\n";

    // Шаблонная фильтрация
    Collection<int> even_numbers = filter_collection(numbers, [](int x) { return x % 2 == 0; });
    std::cout << "\nОтфильтрованные чётные числа:\n" << even_numbers;

    // Удаление элемента
    numbers.remove(45);
    std::cout << "После удаления числа 45:\n" << numbers;

    std::cout << "\n====================================================================\n";
    std::cout << " 2. ТЕСТИРОВАНИЕ Collection<Doctor*> (ПОЛЬЗОВАТЕЛЬСКИЙ ТИП 1)\n";
    std::cout << "====================================================================\n";

    Collection<Doctor*> doctors;
    Doctor* d1 = new Therapist("Иванов И.И.", 10, 520);
    Doctor* d2 = new Surgeon("Петров П.П.", 16, 210);
    Doctor* d3 = new Orthodontist("Сидорова А.А.", 7, 95);
    Doctor* d4 = new Therapist("Васильев В.В.", 3, 80);

    doctors.add(d1);
    doctors += d2;
    doctors += d3;
    doctors += d4;

    std::cout << "Штат врачей клиники (размер: " << doctors.get_size() << "):\n" << doctors;

    // Поиск врача со стажем >= 10 лет
    int docktor_index = find_if(doctors, [](Doctor* d) { return d->get_experience() >= 10; });
    if (docktor_index != -1) {
        std::cout << "Первый опытный специалист (стаж >= 10): " << doctors[docktor_index]->get_name() << "\n";
    }

    // Подсчет среднего коэффициента через шаблонную функцию
    double total_coefficient = calculate_sum(doctors, [](Doctor* d) { return d->get_coefficient(); });
    std::cout << "Суммарный коэффициент штата: " << total_coefficient
              << " (средний: " << total_coefficient / doctors.get_size() << ")\n";

    std::cout << "\n====================================================================\n";
    std::cout << "====================================================================\n";

    Collection<Service*> clinic_services;
    clinic_services.add(new TherapeuticService("Пломбирование зуба", 2500, 40, "24", false, d1));
    clinic_services.add(new SurgicalService("Удаление ретинированного зуба", 5000, 60, "Экстракция", d2));
    clinic_services.add(new OrthodonticService("Установка брекет-системы", 65000, 120, "Брекеты", "Керамика", d3));
    clinic_services.add(new TherapeuticService("Повторное лечение канала", 3200, 50, "24", true, d1));

    std::cout << "Прейскурант услуг клиники:\n" << clinic_services;

    // Фильтрация услуг стоимостью выше 4000 руб.
    Collection<Service*> expensive_services = filter_collection(clinic_services, [](Service* s) {
        return s->get_cost() > 4000;
    });
    std::cout << "\nУслуги стоимостью выше 4000 руб.:\n" << expensive_services;

    // Подсчет общей стоимости каталога услуг
    double total_price = calculate_sum(clinic_services, [](Service* s) { return s->get_cost(); });
    std::cout << "Общая стоимость всех услуг в каталоге: " << total_price << " руб.\n";

    std::cout << "\n====================================================================\n";
    std::cout << " 4. ТЕСТИРОВАНИЕ Collection<Patient> (ПОЛЬЗОВАТЕЛЬСКИЙ ТИП 3)\n";
    std::cout << "====================================================================\n";

    Collection<Patient> patients;
    Patient p1("Смирнов К.А.", true);
    p1 += clinic_services[0];
    p1 += clinic_services[3];

    Patient p2("Ковалёва Е.С.", false);
    p2 += clinic_services[1];

    patients.add(p1);
    patients.add(p2);

    std::cout << "Список пациентов:\n" << patients;

    // Проверка генерации и обработки исключений
    std::cout << "\nПроверка безопасного метода at():\n";
    try {
        std::cout << "Попытка доступа к элементу [10]...\n";
        patients.at(10);
    } catch (const std::out_of_range& e) {
        std::cout << "[Успешный перехват исключения]: " << e.what() << "\n";
    }

    // Освобождение динамической памяти
    for (size_t i = 0; i < doctors.get_size(); ++i) delete doctors[i];
    for (size_t i = 0; i < clinic_services.get_size(); ++i) delete clinic_services[i];

    std::cout << "\nПрограмма успешно завершена. Ресурсы очищены.\n";
    return 0;
}