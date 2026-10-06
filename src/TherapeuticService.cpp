#include "../include/TherapeuticService.h"
#include "../include/Therapist.h"
//#include "../include/Doctor.h"

TherapeuticService::TherapeuticService() : Service(), tooth_number(""), is_repeated(false){}
TherapeuticService::TherapeuticService(std::string serve, int cost, int duration,
    std::string tooth_number, bool is_repeated, Doctor* doctor)
    : Service(serve, cost, duration, nullptr), tooth_number(tooth_number), is_repeated(is_repeated){}
TherapeuticService::~TherapeuticService(){}

std::string TherapeuticService::get_tooth_number() const {return tooth_number;}
bool TherapeuticService::get_is_repeated() const {return is_repeated;}

void TherapeuticService::set_tooth_number(const std::string& tooth_number) {this->tooth_number = tooth_number;}
void TherapeuticService::set_repeat(bool is_repeat) {this->is_repeated = is_repeat;}

bool TherapeuticService::can_accept(Doctor* doctor) const {
    return dynamic_cast<Therapist*>(doctor) != nullptr;
}

std::string TherapeuticService::get_serve_type()const {return "Терапия";}
bool TherapeuticService::is_repeated_service() const {return is_repeated;}

std::ostream& operator<<(std::ostream& os, const TherapeuticService& therapeutic) {
    os << static_cast<const Service&>(therapeutic)
    <<" | Зуб: "<< therapeutic.tooth_number
    <<" | Повторный приём? " << (therapeutic.is_repeated ? "Да" : "Нет");
    return os;
}



