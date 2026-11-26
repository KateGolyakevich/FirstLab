#ifndef CLINIC_FILE_MANAGER_H
#define CLINIC_FILE_MANAGER_H

#include <string>
#include <fstream>
#include <functional>
#include "Collection.hpp"
#include "Doctor.h"
#include "Service.h"
#include "Patient.h"

class ClinicFileManager {
private:
    static const std::string DEFAULT_LOG_FILE;

    static bool with_input_file(const std::string& filename,
                                const std::function<void(std::ifstream&)>& action);

    static bool with_output_file(const std::string& filename,
                                 std::ios_base::openmode mode,
                                 const std::function<void(std::ofstream&)>& action);

    static void write_doctor(std::ofstream& out, Doctor* doc);
    static Doctor* read_doctor(const std::string& line);

    static void write_service(std::ofstream& out, Service* srv);
    static Service* read_service(const std::string& line, const Collection<Doctor*>& doctors);

    static void write_patient(std::ofstream& out, const Patient& patient);
    static bool read_patient(const std::string& line, Patient& out_patient);

    // 3. Микро-парсеры секций файла
    static void parse_doctors_section(std::ifstream& in, size_t count, Collection<Doctor*>& doctors);
    static void parse_services_section(std::ifstream& in, size_t count, Collection<Service*>& services, const Collection<Doctor*>& doctors);
    static void parse_patients_section(std::ifstream& in, size_t count, Collection<Patient>& patients);

    static Doctor* find_doctor_by_name(const Collection<Doctor*>& doctors, const std::string& name);

public:
    static void log(const std::string& message);

    static bool save_system_state(const std::string& filename,
                                  const Collection<Doctor*>& doctors,
                                  const Collection<Service*>& services,
                                  const Collection<Patient>& patients);

    static bool load_system_state(const std::string& filename,
                                  Collection<Doctor*>& doctors,
                                  Collection<Service*>& services,
                                  Collection<Patient>& patients);

    static bool generate_text_report(const std::string& report_filename,
                                     const Collection<Doctor*>& doctors,
                                     const Collection<Service*>& services,
                                     const Collection<Patient>& patients);
};

#endif // CLINIC_FILE_MANAGER_H