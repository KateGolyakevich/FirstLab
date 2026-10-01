#include "../include/Service.h"

Service::Service() : serve(""), cost(0), duration(0) {}

Service::Service(std::string serve, int cost, int duration)
    : serve(serve), cost(cost), duration(duration) {}

Service::~Service() {}

std::string Service::get_serve()const {return serve;}
int Service::get_cost()const {return cost;}
int Service::get_duration()const {return duration;}

void Service::set_serve(const std::string &serve) {this->serve = serve;}
void Service::set_cost(int cost) {if (this->cost > 0) this->cost = cost;}
void Service::set_duration(int duration) {if (this->duration > 0) this->duration = duration;}

std::string Service::get_serve_type() const {return "Общая услуга";}
int Service::get_total_cost()const {return cost;}

std::ostream& operator<<(std::ostream& os, const Service& service) {
    os << "\n | " << service.get_serve_type()
    << " | Цена: " << service.cost
    << " | Длительность: " << service.duration << " мин";
    return os;
}








