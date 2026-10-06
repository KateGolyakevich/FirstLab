#ifndef ORTHODONTIC_H
#define ORTHODONTIC_H

#include "../include/OrthodonticService.h"
#include "../include/Doctor.h"

#include "Service.h"
class OrthodonticService : public Service {
private:
    std::string correction_type;
    std::string correction_material;

public:
    OrthodonticService();
    OrthodonticService(std::string serve, int cost, int duration,
        const std::string& correction_type,
        const std::string& correction_material,
        Doctor* doctor = nullptr);
    ~OrthodonticService() override;

    std::string get_correction_type() const;
    std::string get_correction_material() const;

    void set_correction_type(const std::string& correction_type);
    void set_correction_material(const std::string& correction_material);

    bool can_accept(Doctor* doctor) const override;

    std::string get_serve_type() const override;
    friend std::ostream& operator<<(std::ostream& os, const OrthodonticService& service);
};

#endif //ORTHODONTIC_H
