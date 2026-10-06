#include "../include/OrthodonticService.h"
#include "../include/Orthodontist.h"

OrthodonticService::OrthodonticService(): Service(), correction_type(""), correction_material(""){}

OrthodonticService::OrthodonticService(std::string serve, int cost, int duration,
    const std::string& correction_type,
    const std::string& correction_material,
    Doctor* doctor) : Service(serve, cost, duration, nullptr),
      correction_type(correction_type),
      correction_material(correction_material) {
    set_doctor(doctor);
}

OrthodonticService::~OrthodonticService(){}

std::string OrthodonticService::get_correction_type() const{ return correction_type;}
std::string OrthodonticService::get_correction_material() const{return correction_material;}

void OrthodonticService::set_correction_type(const std::string& correction_type)
{this->correction_type = correction_type;}

void OrthodonticService::set_correction_material(const std::string& correction_material)
{this->correction_material = correction_material;}

bool OrthodonticService::can_accept(Doctor* doctor) const {
    return dynamic_cast<Orthodontist*>(doctor) != nullptr;
}

std::string OrthodonticService::get_serve_type() const {return "Ортодонтия";}

std::ostream& operator<<(std::ostream& os, const OrthodonticService& service)
{os << static_cast<const Service&>(service)
       << " | Устройство (брекеты, капы, пластинка): "
       << service.correction_type
       << " | Материал (металл, керамика, сапфир): "
       << service.correction_material;
    return os;
}