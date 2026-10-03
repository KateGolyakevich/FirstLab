#include "../include/Therapist.h"

Therapist::Therapist() : Doctor(), filled_teeth(0) {}

Therapist::Therapist(std::string name, int experience, int filled_teeth)
    : Doctor(name, experience), filled_teeth(filled_teeth) {}

Therapist::~Therapist() {}

int Therapist::get_filled_teeth() const { return filled_teeth; }
void Therapist::set_filled_teeth(int filled_teeth) { if (filled_teeth >= 0) this->filled_teeth = filled_teeth; }

std::string Therapist::get_specialization() const { return "Терапевт"; }

std::ostream& operator<<(std::ostream& os, const Therapist& therapist) {
    os << static_cast<const Doctor&>(therapist)
       << " | Вылечено зубов: " << therapist.filled_teeth;
    return os;
}