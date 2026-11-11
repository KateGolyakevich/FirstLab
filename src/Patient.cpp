#include "../include/Patient.h"
#include "../exceptions/include_exp/ServiceNotFoundException.h"
#include "../exceptions/include_exp/DuplicatePatientException.h"

Patient::Patient() : name(""), services(), has_card(false) {}

Patient::Patient(const std::string& name, bool has_card)
    : name(name), services(), has_card(has_card) {}

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

int Patient::get_service_count() const {
    return static_cast<int>(services.get_size());
}

void Patient::add_service(Service* service) {
    if (service == nullptr) return;

    for (size_t i = 0; i < services.get_size(); i++) {
        if (services[i] == service) {
            throw DuplicatePatientException(service->get_serve(),this->name);
        }
    }
    services.add(service);
}

bool Patient::remove_service(Service* service) {
    if (service == nullptr || !services.remove(service)) {
        std::string service_title = (service != nullptr) ? service->get_serve() : "NULL";
        throw ServiceNotFoundException(service_title, this->name);
    }
    return true;
}

int Patient::total_service_cost() const {
    int total = 0;
    for (size_t i = 0; i < services.get_size(); ++i) {
        Service* service = services[i];
        int price = service->get_cost();

        if (has_card && service->is_repeated_service()) {
            price = static_cast<int>(price * 0.98);
        }
        total += price;
    }
    return total;
}

Patient& Patient::operator+=(Service* service) {
    add_service(service);
    return *this;
}

Patient& Patient::operator-=(Service* service) {
    remove_service(service);
    return *this;
}

bool Patient::operator==(const Patient& other) const {
    return name == other.name && has_card == other.has_card;
}

std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << "Пациент: " << patient.name
       << " | Карта: " << (patient.has_card ? "Есть" : "Нет")
       << " | Назначено услуг: " << patient.services.get_size()
       << " | Итого к оплате: " << patient.total_service_cost() << " руб.\n";

    for (size_t i = 0; i < patient.services.get_size(); ++i) {
        os << "    (" << (i + 1) << ") " << *(patient.services[i]) << "\n";
    }
    return os;
}