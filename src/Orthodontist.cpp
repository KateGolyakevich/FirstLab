#include "../include/Orthodontist.h"

Orthodontist::Orthodontist() : Doctor(), braces_patients(0) {}

Orthodontist::Orthodontist(std::string name, int experience, int braces_patients)
    : Doctor(name, experience), braces_patients(braces_patients) {}

Orthodontist::~Orthodontist() {}

int Orthodontist::get_braces_patients() const { return braces_patients; }
void Orthodontist::set_braces_patients(int braces_patients) { if (braces_patients >= 0)
    this->braces_patients = braces_patients;}

std::string Orthodontist::get_specialization() const { return "Ортодонт"; }

std::ostream& operator<<(std::ostream& os, const Orthodontist& orthodontist) {
    os << static_cast<const Doctor&>(orthodontist)
       << " | Пациентов с брекетами: " << orthodontist.braces_patients;
    return os;
}
