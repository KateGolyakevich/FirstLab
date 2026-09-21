#include "../include/Service.h"

Service::Service() {
    serve = "";
    doctor_name = "";
    cost = 0;
    duration = 0;
}

Service::Service(std::string serve, std::string doctor_name, int cost, int dur) {
    this->serve = serve;
    this->doctor_name = doctor_name;
    this->cost = cost;
    this->duration = dur;
}

Service::~Service(){}

std::string Service::get_serve() const {return serve;}
std::string Service::get_doctor_name() const {return doctor_name;}
int Service::get_cost() const {return cost;}
int Service::get_duration() const {return duration;}

void Service::set_serve(const std::string &serve) {
    this->serve = serve;
}

void Service::set_doctor_name(const std::string &doctor_name) {
    this->doctor_name = doctor_name;
}

void Service::set_cost(int cost) {
    if (cost >= 0)
        this->cost = cost;
}

void Service::set_duration(int dur) {
    this->duration = dur;
}

void Service::print() {
    std::cout << "Услуга: " << serve << std::endl;
    std::cout << "Врач: " << doctor_name << std::endl;
    std::cout << "Стоимость услуги: " << cost << std::endl;
    std::cout << "Длительность: " << duration << std::endl;
}





