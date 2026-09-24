#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include "Service.h"

class Patient {
private:
    Service services[10];
    int services_count = 0;
    std::string name;
public:
    Patient();
    Patient(const std::string name);

    ~Patient();

    std::string get_name() const;
    void set_name(const std::string& name);
    int get_service_count() const;

    void add_serve(const Service& service);
    void print()const;

    Patient& operator+=(const Service& service);
    Patient& operator-=(const Service& service);

    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
};

#endif