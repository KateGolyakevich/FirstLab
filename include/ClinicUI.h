#ifndef CLINIC_UI_H
#define CLINIC_UI_H

#include <string>
#include "Collection.hpp"
#include "Doctor.h"
#include "Service.h"
#include "Patient.h"

class ClinicUI {
private:
    Collection<Doctor*> doctors;
    Collection<Service*> services;
    Collection<Patient> patients;

    const std::string state_file = "clinic_state.txt";
    const std::string report_file = "clinic_report.txt";
    const std::string log_file = "journal.log";

    int get_int_input(const std::string& prompt);
    void manual_add_doctor();
    void manual_add_patient();
    void show_system_state() const;
    void save_state();
    void load_state();
    void generate_report();
    void seed_initial_data();
    void cleanup_memory();

public:
    ClinicUI();
    ~ClinicUI();

    void run();
};

#endif // CLINIC_UI_H