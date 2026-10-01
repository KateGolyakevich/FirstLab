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

void Patient::add_serve(const Service& service) {
    if (services_count < 10) {
        services[services_count] = service;
        services_count++;
    } else {
        std::cout << "Ошибка: Список услуг полон!" << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << "\n--- Пациент: " << patient.name << " ---" << std::endl;
    os << "Количество процедур: " << patient.services_count << std::endl;
    os << "-----------------------------------" << std::endl;

    for (int i = 0; i < patient.services_count; i++) {
        os << "  " << i + 1 << ". " << patient.services[i] << std::endl;
    }
    os << "-----------------------------------" << std::endl;
    return os;
}

Patient& Patient::operator+=(const Service& service) {
    if (services_count >= 10) {
        std::cout << "Невозможно добавить услугу: список полон." << std::endl;
        return *this;
    }

    for (int i = 0; i < services_count; i++) {
        if (services[i] == service) {
            std::cout << "Услуга \"" << service.get_serve() << "\" уже добавлена пациенту!" << std::endl;
            return *this;
        }
    }

    services[services_count] = service;
    services_count++;
    return *this;
}

Patient& Patient::operator-=(const Service& service) {
    for (int i = 0; i < services_count; i++) {
        if (services[i] == service) {
            for (int j = i; j < services_count - 1; j++) {
                services[j] = services[j + 1];
            }
            services_count--;
            std::cout << "Услуга \"" << service.get_serve() << "\" удалена." << std::endl;
            return *this;
        }
    }
    std::cout << "Услуга \"" << service.get_serve() << "\" не найдена, удаление невозможно." << std::endl;
    return *this;
}


