#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include "Service.h"
#include "Collection.hpp" // Подключаем наш шаблонный контейнер

class Patient {
private:
    std::string name;
    Collection<Service*> services;
    bool has_card;

public:
    Patient();
    explicit Patient(const std::string& name, bool has_card = false);
    ~Patient();

    Patient(const Patient& other);
    Patient& operator=(const Patient& other);

    std::string get_name() const;
    void set_name(const std::string& name);
    bool get_has_card() const;
    void set_has_card(bool has_card);
    int get_service_count() const;

    void add_service(Service* service);
    bool remove_service(Service* service);
    int total_service_cost() const;

    Patient& operator+=(Service* service);
    Patient& operator-=(Service* service);

    bool operator==(const Patient& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
};

#endif // PATIENT_H