#include "../include/Service.h"
#include "../include/Doctor.h"

Service::Service() : serve(""), cost(0), duration(0), doctor(nullptr) {}

Service::Service(std::string serve, int cost, int duration, Doctor* doctor)
    : serve(serve), cost(cost), duration(duration), doctor(nullptr) {
    if (doctor != nullptr) {
        this->doctor = doctor;
    }
}

Service::~Service() {}

std::string Service::get_serve()const {return serve;}
int Service::get_cost()const {
    if (doctor != nullptr) {
        return static_cast<int>(cost * doctor->get_coefficient());
    }
    return cost;
}


int Service::get_duration()const {return duration;}
Doctor* Service::get_doctor() const { return doctor; }

void Service::set_serve(const std::string &serve) {this->serve = serve;}
void Service::set_cost(int cost) {if (cost > 0) this->cost = cost;}
void Service::set_duration(int duration) {if (duration > 0) this->duration = duration;}

bool Service::set_doctor(Doctor* doctor) {
    if (doctor == nullptr || can_accept(doctor)) {
        this->doctor = doctor;
        return true;
    }return false;
}

std::string Service::get_serve_type() const {return "Общая услуга";}
bool Service::is_repeated_service() const {return false;}

std::ostream& operator<<(std::ostream& os, const Service& service) {
    os << "\n | " << service.get_serve_type()
    << " | Цена: " << service.cost
    << " | Длительность: " << service.duration << " мин";
    if (service.doctor != nullptr) {
        os << " | Врач: " << service.doctor->get_name();
    }else {
        os << " | Врач не назначен!";
    }
    return os;
}








