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

void Patient::print() const {
    std::cout << "\n=== Пациент: " << name << " ===" << std::endl;
    std::cout << "Количество процедур: " << services_count << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    for (int i = 0; i < services_count; i++) {
        std::cout << "  " << i + 1 << ". " << services[i] << std::endl;
    }
    std::cout << "-----------------------------------" << std::endl;
}

Patient& Patient::operator+=(const Service& s) {
    if (services_count >= 10) {
        std::cout << "Невозможно добавить услугу: список полон." << std::endl;
        return *this;
    }

    for (int i = 0; i < services_count; i++) {
        if (services[i] == s) {
            std::cout << "Услуга \"" << s.get_serve() << "\" уже добавлена пациенту!" << std::endl;
            return *this;
        }
    }

    services[services_count] = s;
    services_count++;
    return *this;
}

Patient& Patient::operator-=(const Service& s) {
    for (int i = 0; i < services_count; i++) {
        if (services[i] == s) {
            for (int j = i; j < services_count - 1; j++) {
                services[j] = services[j + 1];
            }
            services_count--;
            std::cout << "Услуга \"" << s.get_serve() << "\" удалена." << std::endl;
            return *this;
        }
    }
    std::cout << "Услуга \"" << s.get_serve() << "\" не найдена, удаление невозможно." << std::endl;
    return *this;
}


