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

bool Service::operator==(const Service &other)const{
    return(this->serve == other.serve) && (this->doctor_name == other.doctor_name) &&
        (this->cost == other.cost) && (this->duration == other.duration);
}
bool Service::operator!=(const Service &other)const {
    return(this->serve != other.serve) || (this->doctor_name != other.doctor_name) ||
        (this->cost != other.cost) || (this->duration != other.duration);
}

bool Service::operator<(const Service &other) const {
    return(this->cost < other.cost);
}

bool Service::operator>(const Service &other) const {
    return(this->cost > other.cost);
}

std::ostream& operator<<(std::ostream& os, const Service& service) {
    os << "Услуга: " << service.serve
    << "| Врач: " << service.doctor_name
    << "| Цена: " << service.cost
    << "| Длительность: " << service.duration;
    return os;
}

std::istream& operator>>(std::istream& is, Service& service) {
    std::cout << "Введите название услуги: " << std::endl;
    is >> service.serve;
    std::cout << "Введите ФИО врача: " << std::endl;;
    is >> service.doctor_name;
    std::cout << "Введите стоимость услуги: " << std::endl;;
    is >> service.cost;
    std::cout << "Введите длительность (мин)";
    is >> service.duration;
}

bool is_exspensive(const Service &service, int cost_limit) {
    return service.cost > cost_limit;
}

void Service::print() {
    std::cout << *this << std::endl; // Делегируем вывод оператору <<
}











