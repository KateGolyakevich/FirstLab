#include "../include/Therapeutic.h"

Therapeutic::Therapeutic() : Service(), tooth_number(""), is_repeated(false){}
Therapeutic::Therapeutic(std::string serve, int cost, int duration, std::string tooth_number, bool is_repeated) {}
Therapeutic::~Therapeutic(){}

std::string Therapeutic::get_tooth_number() const {return tooth_number;}
bool Therapeutic::get_is_repeated() const {return is_repeated;}

void Therapeutic::set_tooth_number(const std::string& tooth_number) {this->tooth_number = tooth_number;}
void Therapeutic::set_repeat(bool is_repeat) {this->is_repeated = is_repeat;}

std::string Therapeutic::get_serve_type()const {return "Терапия";}

bool Therapeutic::is_repeated_service() const {return is_repeated;}

std::ostream& operator<<(std::ostream& os, const Therapeutic& service) {
    os << static_cast<const Service&>(service)
    <<" | Зуб: "<< service.tooth_number
    <<" | Повторный приём? " << (service.is_repeated ? "Да" : "Нет");
    return os;
}



