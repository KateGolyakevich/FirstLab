#include "../include/Service.h"
#include "../include/Doctor.h"

Service::Service() : serve(""), cost(0), duration(0), doctor(nullptr) {}

Service::Service(std::string serve, int cost, int duration, Doctor* doctor)
    : serve(serve), cost(cost), duration(duration), doctor(doctor) {}

Service::~Service() {}

std::string Service::get_serve()const {return serve;}
int Service::get_cost()const {return cost;}
int Service::get_duration()const {return duration;}
Doctor* Service::get_doctor() const { return doctor; }

void Service::set_serve(const std::string &serve) {this->serve = serve;}
void Service::set_cost(int cost) {if (this->cost > 0) this->cost = cost;}
void Service::set_duration(int duration) {if (this->duration > 0) this->duration = duration;}
void Service::set_doctor(Doctor* doctor) {this->doctor = doctor;}

std::string Service::get_serve_type() const {return "Общая услуга";}
bool Service::is_repeated_service() const {return false;}

std::ostream& operator<<(std::ostream& os, const Service& service) {
    os << "\n | " << service.get_serve_type()
    << " | Цена: " << service.cost
    << " | Длительность: " << service.duration << " мин"
    << " | Врач: " << service.doctor -> get_name();
    return os;
}








