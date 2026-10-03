#include "../include/Surgical.h"

Surgical::Surgical() : Service(), operation_type("") {}
Surgical::Surgical(std::string serve, int cost, int duration, std::string operation_type) {}
Surgical::~Surgical(){}

std::string Surgical::get_operation_type() const {return operation_type;}
void Surgical::set_operation_type(const std::string& operation_type) {this->operation_type = operation_type;}

std::string Surgical::get_serve_type() const {return "Хирургия";}

std::ostream& operator<<(std::ostream& os, const Surgical& service) {
    os << static_cast<const Service&>(service)
    << " | Операция: " << service.get_operation_type();
    return os;
}