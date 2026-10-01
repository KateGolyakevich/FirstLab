#include <iostream>
#include "../include/Patient.h"
#include "../include/Service.h"

int main() {

    std::cout << "---Создание услуг---" << std::endl;
    Service serve_first("Удаление кариеса", "Иванов И.И.", 500, 45);
    Service serve_second("Рентген", "Петров П.П.", 1200, 20);
    Service serve_third("Протезирование", "Сидорова А.А.", 8000, 40);

    std::cout << serve_first << std::endl;
    std::cout << serve_second << std::endl;
    std::cout << serve_third << std::endl;

    std::cout << "\n---Сравнение по цене---" << std::endl;
    if (serve_second > serve_first) {
        std::cout << "Услуга: " << serve_second.get_serve() << " дороже " << serve_first.get_serve()<< std::endl;
    }else {
        std::cout << "Услуга: " << serve_second.get_serve() << " дешевле " << serve_first.get_serve()<< std::endl;
    }

    std::cout << "\n---Сравнение двух услуг по характеристикам:---" << std::endl;
    Service serve_fourth("Удаление кариеса", "Иванов И.И.", 550, 15);
    if (serve_first == serve_fourth) {
        std::cout << "Это одна и та же услуга." << std::endl;
    } else {
        std::cout << "Услуги разные." << std::endl;
    }

    if (is_expensive(serve_second, 1000)) {
        std::cout << "Услуга " << serve_second.get_serve() << " является дорогой (>1000)." << std::endl;
    }

    std::cout << "\n---Создание новой услуги ---" << std::endl;
    Service serve_five;
    std::cin >> serve_five;
    std::cout << "\nВы ввели: " << serve_five << std::endl;

    Patient patient("Смирнов Алексей Владимирович");

    patient += serve_first;
    patient += serve_second;
    patient += serve_third;

    std::cout << "\nПытаемся добавить дубликат " << serve_first.get_serve() << std::endl;
    patient += serve_first;

    std::cout << "\nТекущее состояние пациента:" << std::endl;
    std::cout << patient;

    std::cout << "\nУдаляем услугу " << serve_second.get_serve() << std::endl;
    patient -= serve_second;

    std::cout << "\nСостояние после удаления:" << std::endl;
    std::cout << patient;


    return 0;
}