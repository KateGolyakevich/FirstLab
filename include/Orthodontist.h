#ifndef ORTHODONTIST_H
#define ORTHODONTIST_H

#include "Doctor.h"

class Orthodontist : public Doctor {
    private:
    int braces_patients;

    public:
    Orthodontist();
    Orthodontist(std::string name, int experience, int braces_patients);
    ~Orthodontist() override;

    int get_braces_patients() const;
    void set_braces_patients(int count);

    std::string get_doctor_type() const override;
    double get_coefficient() const override;
    void perform_procedure() const override;
    void print_info(std::ostream& os) const override;
};

#endif
