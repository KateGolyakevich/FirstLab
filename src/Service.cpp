#include "../include/Service.h"
#include <iomanip>

Service::Service()
    : serve(""),
      doctor_name(""),
      cost(0),
      duration(0)
{}


Service::Service(std::string serve, std::string doctor_name, int cost, int duration)
    : serve(serve),
      doctor_name(doctor_name),
      cost(cost),
      duration(duration)
{}


Service::~Service() {}

std::string Service::get_serve() const {return serve;}
std::string Service::get_doctor_name() const {return doctor_name;}
int Service::get_cost() const {return cost;}
int Service::get_duration() const {return duration;}

void Service::set_serve(const std::string& serve) { this->serve = serve; }
void Service::set_doctor_name(const std::string& doctor) { this->doctor_name = doctor; }
void Service::set_cost(int cost) { if(cost >= 0) this->cost = cost; }
void Service::set_duration(int duration) { if(duration >= 0) this->duration = duration; }

bool Service::operator==(const Service &service)const{
    return(this->serve == service.serve) && (this->doctor_name == service.doctor_name) &&
        (this->cost == service.cost) && (this->duration == service.duration);
}
bool Service::operator!=(const Service &service)const {
    return(this->serve != service.serve) || (this->doctor_name != service.doctor_name) ||
        (this->cost != service.cost) || (this->duration != service.duration);
}

bool Service::operator<(const Service &service) const {
    return(this->cost < service.cost);
}

bool Service::operator>(const Service &service) const {
    return(this->cost > service.cost);
}

std::ostream& operator<<(std::ostream& os, const Service& service) {
    os << "Услуга: " << service.serve
    << "| Врач: " << service.doctor_name
    << "| Цена: " << service.cost
    << "| Длительность: " << service.duration;
    return os;
}

std::istream& operator>>(std::istream& is, Service& service) {
    std::cout << "Введите название услуги: ";
    std::getline(is >> std::ws, service.serve);
    std::cout << "Введите ФИО врача: ";
    std::getline(is >> std::ws, service.doctor_name);
    std::cout << "Введите стоимость услуги: ";
    is >> service.cost;
    std::cout << "Введите длительность (мин): ";
    is >> service.duration;
    return is;
}

bool is_expensive(const Service &service, int cost_limit) {
    return service.cost > cost_limit;
}












