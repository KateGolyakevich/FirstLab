#include "../include/Therapist.h"

Therapist::Therapist() : Doctor(), filled_teeth(0) {}

Therapist::Therapist(std::string name, int experience, int filled_teeth)
    : Doctor(name, experience), filled_teeth(filled_teeth) {}

Therapist::~Therapist() {}

int Therapist::get_filled_teeth() const { return filled_teeth; }
void Therapist::set_filled_teeth(int filled_teeth) {
    if (filled_teeth >= 0) this->filled_teeth = filled_teeth;
}

std::string Therapist::get_doctor_type() const { return "Терапевт"; }

// Специфический расчет коэффициента: базовый + 3% за год стажа + бонус за вылеченные зубы
double Therapist::get_coefficient() const {
    return 1.0 + (experience * 0.03) + (filled_teeth * 0.0005);
}

void Therapist::perform_procedure() const {
    std::cout << "Врач-терапевт " << name << " проводит эндодонтическое лечение и установку пломбы." << std::endl;
}

void Therapist::print_info(std::ostream& os) const {
    Doctor::print_info(os);
    os << " | Вылечено зубов: " << filled_teeth;
}