#ifndef CLINICFILEMANAGER_H
#define CLINICFILEMANAGER_H

#include <string>
#include <fstream>
#include "Collection.hpp"
#include "Doctor.h"
#include "Service.h"
#include "Patient.h"

class ClinicFileManager {
    public:
    static void log_event(const std::string& log_file_name, const std::string& message);

    static bool save_system_state(const std::string& filename,
        const Collection<Doctor*>& doctors, const Collection<Service*>& services, const Collection<Patient*>& patients);

    static bool load_system_state(const std::string& filename,
        Collection<Doctor*>& doctors, Collection<Service*>& services, Collection<Patient*>& patients);

    static bool generate_text_report(const std::string& report_filename,
        const Collection<Doctor*>& doctors, const Collection<Service*>& services, Collection<Patient*>& patients);

    private:
    static void save_single_doctor(std::ofstream& out, Doctor* doctor);
    static Doctor* load_single_doctor(const std::string& line);

    static void save_single_service(std::ofstream& out, Service* service);
    static Service* load_single_service(const std::string& line, const Collection<Doctor*>& doctors);

    static Doctor* find_doctor_by_name(const Collection<Doctor*>& doctors, const std::string& name);
    static Service* find_doctor_by_name(const Collection<Service*>& services, const std::string& name);
};


#endif //CLINICFILEMANAGER_H
