#include "../include/TherapeuticService.h"

TherapeuticService::TherapeuticService()
    : Service(), tooth_number(""), is_repeated(false) {}

TherapeuticService::TherapeuticService(std::string serve, int cost, int duration,
                                       std::string tooth_number, bool is_repeated, Doctor* doctor)
    : Service(serve, cost, duration, nullptr), tooth_number(tooth_number), is_repeated(is_repeated) {
    set_doctor(doctor);
}

TherapeuticService::~TherapeuticService() {}

std::string TherapeuticService::get_tooth_number() const { return tooth_number; }
bool TherapeuticService::get_is_repeated() const { return is_repeated; }

void TherapeuticService::set_tooth_number(const std::string& tn) { tooth_number = tn; }
void TherapeuticService::set_repeat(bool is_repeat) { is_repeated = is_repeat; }

std::string TherapeuticService::get_serve_type() const { return "Терапия"; }

bool TherapeuticService::can_accept(Doctor* doctor) const {
    return dynamic_cast<Therapist*>(doctor) != nullptr;
}

bool TherapeuticService::is_repeated_service() const { return is_repeated; }

void TherapeuticService::execute_service() const {
    std::cout << "-> Выполняется терапия зуба №" << tooth_number
              << (is_repeated ? " (повторный приём)" : " (первичный осмотр)")
              << ". Лечение проводит " << (doctor ? doctor->get_name() : "дежурный врач") << "." << std::endl;
}

void TherapeuticService::print_info(std::ostream& os) const {
    Service::print_info(os);
    os << " | Номер зуба: " << tooth_number
       << " | Повторный приём: " << (is_repeated ? "Да" : "Нет");
}

