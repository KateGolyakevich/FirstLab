#include "../include/Patient.h"

Patient::Patient() : name(""), has_card(false) {}

Patient::Patient(const std::string& name, bool has_card)
    : name(name), has_card(has_card) {}

Patient::~Patient() {
    services.clear();
}

Patient::Patient(const Patient& other)
    : name(other.name), services(other.services), has_card(other.has_card) {}

Patient& Patient::operator=(const Patient& other) {
    if (this != &other) {
        name = other.name;
        services = other.services;
        has_card = other.has_card;
    }
    return *this;
}

std::string Patient::get_name() const { return name; }
void Patient::set_name(const std::string& name) { this->name = name; }
bool Patient::get_has_card() const { return has_card; }
void Patient::set_has_card(bool has_card) { this->has_card = has_card; }
int Patient::get_service_count() const { return static_cast<int>(services.size()); }

void Patient::add_service(Service* service) {
    if (service) services.push_back(service);
}

int Patient::total_service_cost() const {
    int total = 0;
    for (const auto* service : services) {
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

bool Patient::operator==(const Patient& other) const {
    return name == other.name && has_card == other.has_card;
}

std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << "Пациент: " << patient.name
       << " | Карта: " << (patient.has_card ? "Есть" : "Нет")
       << " | Услуг назначено: " << patient.services.size()
       << " | Итого к оплате: " << patient.total_service_cost() << " руб.";
    return os;
}