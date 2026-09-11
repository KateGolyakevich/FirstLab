#include <iostream>
#include <string>

class Service{
public:
    std::string serve_name;
    std::string doctor_name;
    int serve_cost;
    int duration;

    void print() {
        std::cout << "Услуга: " << serve_name << std::endl;
        std::cout << "Врач: " << doctor_name << std::endl;
        std::cout << "Стоимость услуги: " << serve_cost << ".руб " <<  std::endl;
        std::cout << "Продолжительность приёма: " << duration << std::endl;
    }
};

