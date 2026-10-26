#include "../include/Orthodontist.h"

Orthodontist::Orthodontist() : Doctor(), braces_patients(0) {}

Orthodontist::Orthodontist(std::string name, int experience, int braces_patients)
    : Doctor(name, experience), braces_patients(braces_patients) {}

Orthodontist::~Orthodontist() {}

int Orthodontist::get_braces_patients() const { return braces_patients; }
void Orthodontist::set_braces_patients(int count) {
    if (count >= 0) this->braces_patients = count;
}

std::string Orthodontist::get_doctor_type() const { return "Ортодонт"; }

// Специфический расчет коэффициента ортодонта
double Orthodontist::get_coefficient() const {
    return 1.1 + (experience * 0.035) + (braces_patients * 0.002);
}

void Orthodontist::perform_procedure() const {
    std::cout << "Ортодонт " << name << " выполняет коррекцию прикуса и настройку брекет-системы." << std::endl;
}

void Orthodontist::print_info(std::ostream& os) const {
    Doctor::print_info(os);
    os << " | Пациентов с брекетами: " << braces_patients;
}
