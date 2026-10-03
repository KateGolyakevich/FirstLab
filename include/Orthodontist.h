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
    void set_braces_patients(int braces_patients);

    std::string get_doctor_type() const override;

    friend std::ostream& operator<<(std::ostream& os, const Orthodontist& orthodontist);
};

#endif
