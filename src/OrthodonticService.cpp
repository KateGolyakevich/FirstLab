#include "../include/OrthodonticService.h"

OrthodonticService::OrthodonticService()
    : Service(), correction_type(""), correction_material("") {}

OrthodonticService::OrthodonticService(std::string serve, int cost, int duration,
                                       std::string correction_type, std::string correction_material,
                                       Doctor* doctor)
    : Service(serve, cost, duration, nullptr),
      correction_type(correction_type),
      correction_material(correction_material) {
    set_doctor(doctor);
}

OrthodonticService::~OrthodonticService() {}

std::string OrthodonticService::get_correction_type() const { return correction_type; }
std::string OrthodonticService::get_correction_material() const { return correction_material; }

void OrthodonticService::set_correction_type(const std::string& t) { correction_type = t; }
void OrthodonticService::set_correction_material(const std::string& m) { correction_material = m; }

std::string OrthodonticService::get_serve_type() const { return "Ортодонтия"; }

bool OrthodonticService::can_accept(Doctor* doctor) const {
    return dynamic_cast<Orthodontist*>(doctor) != nullptr;
}

void OrthodonticService::execute_service() const {
    std::cout << "-> Установка/коррекция ортодонтической конструкции: " << correction_type
              << " (материал: " << correction_material << ")." << std::endl;
}

void OrthodonticService::print_info(std::ostream& os) const {
    Service::print_info(os);
    os << " | Аппарат: " << correction_type
       << " | Материал: " << correction_material;
}