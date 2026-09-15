#include "../include/Service.h"

void Service::print() {
    std::cout << "Услуга: " << serve_name << std::endl;
    std::cout << "Врач: " << doctor_name << std::endl;
    std::cout << "Длительность: " << duration << std::endl;
    std::cout << "Стоимость услуги: " << serve_cost << std::endl;
}


