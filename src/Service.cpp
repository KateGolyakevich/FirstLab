#include "../include/Service.h"

Service::Service() : serve(""), cost(0), duration(0), doctor(nullptr) {}

Service::Service(std::string serve, int cost, int duration, Doctor* doctor)
    : serve(serve), cost(cost), duration(duration), doctor(nullptr) {
    if (doctor != nullptr) {
        set_doctor(doctor);
    }
}

Service::~Service() {}

std::string Service::get_serve() const { return serve; }
int Service::get_duration() const { return duration; }
Doctor* Service::get_doctor() const { return doctor; }

void Service::set_serve(const std::string& serve) { this->serve = serve; }
void Service::set_cost(int cost) { if (cost > 0) this->cost = cost; }
void Service::set_duration(int duration) { if (duration > 0) this->duration = duration; }

bool Service::set_doctor(Doctor* doc) {
    if (doc == nullptr || can_accept(doc)) {
        this->doctor = doc;
        return true;
    }
    std::cout << "[Ошибка] Врач " << doc->get_name()
              << " (" << doc->get_doctor_type()
              << ") не имеет допуска к услуге типа: " << get_serve_type() << std::endl;
    return false;
}

int Service::get_cost() const {
    if (doctor != nullptr) {
        return static_cast<int>(cost * doctor->get_coefficient());
    }
    return cost;
}

bool Service::is_repeated_service() const { return false; }

void Service::print_info(std::ostream& os) const {
    os << "Услуга: \"" << serve << "\" (" << get_serve_type() << ")"
       << " | Базовая цена: " << cost << " руб."
       << " | Итоговая: " << get_cost() << " руб."
       << " | Длительность: " << duration << " мин.";
    if (doctor != nullptr) {
        os << " | Врач: " << doctor->get_name();
    } else {
        os << " | [Врач не назначен!]";
    }
}

std::ostream& operator<<(std::ostream& os, const Service& service) {
    service.print_info(os);
    return os;
}