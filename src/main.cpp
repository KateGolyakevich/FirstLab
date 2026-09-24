#include <iostream>
#include "../include/Patient.h"
#include "../include/Service.h"

int main() {

    std::cout << "1. Создание услуг:" << std::endl;
    Service serve_first("Удаление кариесса", "Иванов И.И.", 500, 45);
    Service serve_second("Рентген", "Петров П.П.", 1200, 20);
    Service serve_third("Протезирование", "Сидорова А.А.", 8000, 40);

    std::cout << serve_first << std::endl;
    std::cout << serve_second << std::endl;
    std::cout << serve_third << std::endl;

    std::cout << "\nСравнение по цене" << std::endl;
    if (serve_second > serve_first) {
        std::cout << "Рентген дороже удаление кариесса." << std::endl;
    }

    // Проверка на равенство
    Service serve_fourth("Удаление кариесса", "Иванов И.И.", 550, 15); // Другая цена, но тот же врач и название
    if (serve_first == serve_fourth) {
        std::cout << "Это одна и та же услуга." << std::endl;
    } else {
        std::cout << "Услуги разные." << std::endl;
    }

    if (is_expensive(serve_second, 1000)) {
        std::cout << "Услуга \"" << serve_second.get_serve() << "\" является дорогой (>1000)." << std::endl;
    }

    Service serve_five;
    std::cin >> serve_five;
    std::cout << "Вы ввели: " << serve_five << std::endl;

    Patient patient("Смирнов Алексей");

    patient += serve_first;
    patient += serve_second;
    patient += serve_third;

    //std::cout << "\nПытаемся добавить дубликат удаление кариесса:" << std::endl;
    //patient += serve_first;

    std::cout << "\nТекущее состояние пациента:" << std::endl;
    patient.print();

    std::cout << "\nУдаляем услугу 'Рентген'..." << std::endl;
    patient -= serve_second;

    std::cout << "\nСостояние после удаления:" << std::endl;
    patient.print();


    return 0;
}