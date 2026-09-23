#include "../include/Service.h"
#include <iomanip>

Service::Service() : serve("Не указано"), doctor_name("Не указано"), cost(0), duration(0) {}

Service::Service(const std::string& serve, const std::string& doctor_name, int cost, int dur)
    : serve(serve), doctor_name(doctor_name), cost(cost), duration(dur) {}

Service::~Service(){}

std::string Service::get_serve() const {return serve;}
std::string Service::get_doctor_name() const {return doctor_name;}
int Service::get_cost() const {return cost;}
int Service::get_duration() const {return duration;}

void Service::set_serve(const std::string& name) { this->serve = name; }
void Service::set_doctor_name(const std::string& doctor) { this->doctor_name = doctor; }
void Service::set_cost(int cost) { if(cost >= 0) this->cost = cost; }
void Service::set_duration(int dur) { if(dur >= 0) this->duration = dur; }

bool Service::operator==(const Service &other)const{
    return(this->serve == other.serve) && (this->doctor_name == other.doctor_name) &&
        (this->cost == other.cost) && (this->duration == other.duration);
}
bool Service::operator!=(const Service &other)const {
    return(this->serve != other.serve) || (this->doctor_name != other.doctor_name) ||
        (this->cost != other.cost) || (this->duration != other.duration);
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
    std::cout << "";
    is >> service.serve;
    std::cout << "";
    is >> service.doctor_name;
    std::cout << "";
    is >> service.cost;
    std::cout << "";
    is >> service.duration;
}

bool is_exspensive(const Service &service, int cost_limit) {
    return service.cost > cost_limit;
}

void Service::print() {
    std::cout << *this << std::endl; // Делегируем вывод оператору <<
}











