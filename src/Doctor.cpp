#include "../include/Doctor.h"

Doctor::Doctor() : name(""), experience(0) {}
Doctor::Doctor(std::string name, int experience) : name(name), experience(experience) {}
Doctor::~Doctor() {}

std::string Doctor::get_name() const{return name;}
int Doctor::get_experience() const{return experience;}

void Doctor::set_name(const std::string &name) {this->name = name;}
void Doctor::set_experience(int experience) {if (experience > 0)this->experience = experience;}

std::string Doctor::get_doctor_type() const { return "Врач";}
double Doctor::get_coefficient() const {return 1.0;}

std::ostream& operator<<(std::ostream& os, const Doctor& doctor) {
    os << "\n [ " << doctor.get_doctor_type() << "]" << doctor.name
    << " | Стаж:" << doctor.get_experience();
    return os;
}









