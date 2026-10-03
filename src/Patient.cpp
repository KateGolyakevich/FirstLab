#include "../include/Patient.h"

Patient::Patient() : name(""), has_card(false) {}

Patient::Patient(const std::string& name, bool has_card)
    : name(name), has_card(has_card) {}

Patient::~Patient() {
    for (auto* service : services) delete service;
    services.clear();
}

std::string Patient::get_name() const { return name; }
void Patient::set_name(const std::string& name) { this->name = name; }

bool Patient::get_has_card() const { return has_card; }
void Patient::set_has_card(bool has_card) { this->has_card = has_card; }

int Patient::get_service_count() const { return static_cast<int>(services.size()); }

void Patient::add_service(Service* service) {
    if (service) services.push_back(service);
}

int Patient::total_service_count() const {
    int total = 0;
    for (auto* service : services) {
        int price = service->get_cost();

        if (has_card && service->is_repeated_service()) {
            price = static_cast<int>(price * 0.98);
        }
        total += price;
    }
    return total;
}

Patient& Patient::operator+=(Service* service) {
    if (service) services.push_back(service);
    return *this;
}

Patient& Patient::operator-=(Service* service) {
    for (auto it = services.begin(); it != services.end(); ++it) {
        if (*it == service) {
            delete *it;
            services.erase(it);
            std::cout << "Услуга удалена." << std::endl;
            return *this;
        }
    }
    std::cout << "Услуга не найдена." << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << "Пациент: " << patient.name
       << " | Карта: " << (patient.has_card ? "есть" : "нет")
       << " | Записей: " << patient.services.size()
       << " | Итого: " << patient.total_service_count() << " руб.";
    return os;
}

