#include "../include/Doctor.h"
#include "../exceptions/include_exp/InvalidDataException.h"

Doctor::Doctor() : name(""), experience(0) {}

Doctor::Doctor(std::string name, int experience)
    : name(name), experience(0) {set_experience(experience);}

Doctor::~Doctor() {}

std::string Doctor::get_name() const { return name; }
int Doctor::get_experience() const { return experience; }

void Doctor::set_name(const std::string& name) { this->name = name; }

void Doctor::set_experience(int experience) {
    if (experience < 0) {
        throw InvalidDataException("experience", "Стаж врача не может быть отрицательным (" + std::to_string(experience) + ")");
    }
    this->experience = experience;
}

void Doctor::print_info(std::ostream& os) const {
    os << "[" << get_doctor_type() << "] " << name
       << " | Стаж: " << experience << " лет"
       << " | Коэффициент: " << get_coefficient();
}

std::ostream& operator<<(std::ostream& os, const Doctor& doctor) {
    doctor.print_info(os);
    return os;
}








