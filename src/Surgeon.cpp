#include "../include/Surgeon.h"

Surgeon::Surgeon() : Doctor(), operations_count(0) {}

Surgeon::Surgeon(std::string name, int experience, int operations_count)
    : Doctor(name, experience), operations_count(operations_count) {}

Surgeon::~Surgeon() {}

int Surgeon::get_operations_count() const { return operations_count; }
void Surgeon::set_operations_count(int count) {
    if (count >= 0) this->operations_count = count;
}

std::string Surgeon::get_doctor_type() const { return "Хирург"; }

// Специфический расчет коэффициента хирурга
double Surgeon::get_coefficient() const {
    return 1.15 + (experience * 0.04) + (operations_count * 0.001);
}

void Surgeon::perform_procedure() const {
    std::cout << "Хирург " << name << " выполняет оперативное вмешательство под анестезией." << std::endl;
}

void Surgeon::print_info(std::ostream& os) const {
    Doctor::print_info(os);
    os << " | Проведено операций: " << operations_count;
}