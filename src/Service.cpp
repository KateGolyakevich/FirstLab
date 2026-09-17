#include "../include/Service.h"

void Service::print() {
    std::cout << "Услуга: " << name << std::endl;
    std::cout << "Врач: " << doctor_name << std::endl;
    std::cout << "Длительность: " << duration << std::endl;
    std::cout << "Стоимость услуги: " << cost << std::endl;
}


