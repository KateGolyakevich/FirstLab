#include "../include/Surgeon.h"

Surgeon::Surgeon() : Doctor(), operations_count(0) {}

Surgeon::Surgeon(std::string name, int experience, int ops)
    : Doctor(name, experience), operations_count(ops) {}

Surgeon::~Surgeon() {}

int Surgeon::get_operations_count() const { return operations_count; }
void Surgeon::set_operations_count(int operations_count) { if (operations_count >= 0)
    this->operations_count = operations_count; }

std::string Surgeon::get_specialization() const { return "Хирург"; }

std::ostream& operator<<(std::ostream& os, const Surgeon& surgeon) {
    os << static_cast<const Doctor&>(surgeon)
       << " | Проведено операций: " << surgeon.operations_count;
    return os;
}