#include "../include/Patient.h"

Patient::Patient() {
    this->name = "";
    this->services_count = 0;
}

Patient::Patient(const std::string name) {
    this->name = name;
    this->services_count = 0;
}

Patient::~Patient(){}

std::string Patient::get_name() const {
    return name;
}

void Patient::set_name(const std::string& name) {
    this->name = name;
}
int Patient::get_service_count() const {
    return services_count;
}

void Patient::add_serve(Service service) {
    if (services_count < 10) {
        this->services[services_count] = service;
        this->services_count++;
    }else {
        std::cout << "Невозможно добавить ещё услугу. Список полон" << std::endl;
    }
}

void Patient::print() {
    std::cout << "\nПациент: " << name << std::endl;
    std::cout << "Количество процедур: " << services_count << std::endl;
    for (int i = 0; i < services_count; i++) {
        std::cout << "\nПроцедура: " << i+1 << ":" << std::endl;
        services[i].print();
    }
}


