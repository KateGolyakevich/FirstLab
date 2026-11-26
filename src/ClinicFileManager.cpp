#include "../include/ClinicFileManager.h"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include <sstream>
#include <ctime>

const std::string ClinicFileManager::DEFAULT_LOG_FILE = "journal.log";

bool ClinicFileManager::with_input_file(const std::string& filename,
                                        const std::function<void(std::ifstream&)>& action) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    action(file);
    file.close();
    return true;
}

bool ClinicFileManager::with_output_file(const std::string& filename,
                                         std::ios_base::openmode mode,
                                         const std::function<void(std::ofstream&)>& action) {
    std::ofstream file(filename, mode);
    if (!file.is_open()) return false;
    action(file);
    file.close();
    return true;
}

void ClinicFileManager::log(const std::string& message) {
    with_output_file(DEFAULT_LOG_FILE, std::ios::app, [&message](std::ofstream& out) {
        std::time_t now = std::time(nullptr);
        char buf[26];
        ctime_r(&now, buf);
        std::string time_str(buf);
        if (!time_str.empty() && time_str.back() == '\n') time_str.pop_back();

        out << "[" << time_str << "] " << message << "\n";
    });
}

Doctor* ClinicFileManager::find_doctor_by_name(const Collection<Doctor*>& doctors, const std::string& name) {
    for (size_t i = 0; i < doctors.get_size(); ++i) {
        if (doctors[i]->get_name() == name) return doctors[i];
    }
    return nullptr;
}

void ClinicFileManager::write_doctor(std::ofstream& out, Doctor* doc) {
    out << doc->get_doctor_type() << ";" << doc->get_name() << ";" << doc->get_experience() << ";";
    if (auto* t = dynamic_cast<Therapist*>(doc)) out << t->get_filled_teeth();
    else if (auto* s = dynamic_cast<Surgeon*>(doc)) out << s->get_operations_count();
    else if (auto* o = dynamic_cast<Orthodontist*>(doc)) out << o->get_braces_patients();
    out << "\n";
}

Doctor* ClinicFileManager::read_doctor(const std::string& line) {
    std::stringstream ss(line);
    std::string type, name, exp_s, spec_s;
    if (!std::getline(ss, type, ';') || !std::getline(ss, name, ';') ||
        !std::getline(ss, exp_s, ';') || !std::getline(ss, spec_s)) return nullptr;

    int exp = std::stoi(exp_s), spec = std::stoi(spec_s);
    if (type == "Терапевт") return new Therapist(name, exp, spec);
    if (type == "Хирург")   return new Surgeon(name, exp, spec);
    if (type == "Ортодонт") return new Orthodontist(name, exp, spec);
    return nullptr;
}

void ClinicFileManager::write_service(std::ofstream& out, Service* srv) {
    std::string doc_name = srv->get_doctor() ? srv->get_doctor()->get_name() : "NONE";
    out << srv->get_serve_type() << ";" << srv->get_serve() << ";"
        << srv->get_cost() << ";" << srv->get_duration() << ";" << doc_name << ";";

    if (auto* t = dynamic_cast<TherapeuticService*>(srv)) {
        out << t->get_tooth_number() << ";" << (t->get_is_repeated() ? "1" : "0");
    } else if (auto* s = dynamic_cast<SurgicalService*>(srv)) {
        out << s->get_operation_type();
    } else if (auto* o = dynamic_cast<OrthodonticService*>(srv)) {
        out << o->get_correction_type() << ";" << o->get_correction_material();
    }
    out << "\n";
}

Service* ClinicFileManager::read_service(const std::string& line, const Collection<Doctor*>& doctors) {
    std::stringstream ss(line);
    std::string type, serve, cost_s, dur_s, doc_name;
    if (!std::getline(ss, type, ';') || !std::getline(ss, serve, ';') ||
        !std::getline(ss, cost_s, ';') || !std::getline(ss, dur_s, ';') ||
        !std::getline(ss, doc_name, ';')) return nullptr;

    int cost = std::stoi(cost_s), dur = std::stoi(dur_s);
    Doctor* doc = (doc_name != "NONE") ? find_doctor_by_name(doctors, doc_name) : nullptr;

    if (type == "Терапия") {
        std::string tooth, rep_s;
        std::getline(ss, tooth, ';'); std::getline(ss, rep_s);
        return new TherapeuticService(serve, cost, dur, tooth, rep_s == "1", doc);
    } else if (type == "Хирургия") {
        std::string op; std::getline(ss, op);
        return new SurgicalService(serve, cost, dur, op, doc);
    } else if (type == "Ортодонтия") {
        std::string corr, mat;
        std::getline(ss, corr, ';'); std::getline(ss, mat);
        return new OrthodonticService(serve, cost, dur, corr, mat, doc);
    }
    return nullptr;
}

void ClinicFileManager::write_patient(std::ofstream& out, const Patient& patient) {
    out << patient.get_name() << ";" << (patient.get_has_card() ? "1" : "0") << "\n";
}

bool ClinicFileManager::read_patient(const std::string& line, Patient& out_patient) {
    std::stringstream ss(line);
    std::string name, card_s;
    if (std::getline(ss, name, ';') && std::getline(ss, card_s)) {
        out_patient = Patient(name, card_s == "1");
        return true;
    }
    return false;
}

void ClinicFileManager::parse_doctors_section(std::ifstream& in, size_t count, Collection<Doctor*>& doctors) {
    std::string line;
    for (size_t i = 0; i < count && std::getline(in, line); ++i) {
        if (Doctor* d = read_doctor(line)) doctors.add(d);
    }
}

void ClinicFileManager::parse_services_section(std::ifstream& in, size_t count, Collection<Service*>& services, const Collection<Doctor*>& doctors) {
    std::string line;
    for (size_t i = 0; i < count && std::getline(in, line); ++i) {
        if (Service* s = read_service(line, doctors)) services.add(s);
    }
}

void ClinicFileManager::parse_patients_section(std::ifstream& in, size_t count, Collection<Patient>& patients) {
    std::string line;
    for (size_t i = 0; i < count && std::getline(in, line); ++i) {
        Patient p;
        if (read_patient(line, p)) patients.add(p);
    }
}

bool ClinicFileManager::save_system_state(const std::string& filename,
                                          const Collection<Doctor*>& doctors,
                                          const Collection<Service*>& services,
                                          const Collection<Patient>& patients) {
    bool success = with_output_file(filename, std::ios::trunc, [&](std::ofstream& out) {
        out << "[DOCTORS] " << doctors.get_size() << "\n";
        for (size_t i = 0; i < doctors.get_size(); ++i) write_doctor(out, doctors[i]);

        out << "[SERVICES] " << services.get_size() << "\n";
        for (size_t i = 0; i < services.get_size(); ++i) write_service(out, services[i]);

        out << "[PATIENTS] " << patients.get_size() << "\n";
        for (size_t i = 0; i < patients.get_size(); ++i) write_patient(out, patients[i]);
    });

    if (success) log("Сохранено состояние системы в: " + filename);
    return success;
}

bool ClinicFileManager::load_system_state(const std::string& filename,
                                          Collection<Doctor*>& doctors,
                                          Collection<Service*>& services,
                                          Collection<Patient>& patients) {
    return with_input_file(filename, [&](std::ifstream& in) {
        doctors.clear();
        services.clear();
        patients.clear();

        std::string line;
        while (std::getline(in, line)) {
            if (line.find("[DOCTORS]") == 0) {
                parse_doctors_section(in, std::stoul(line.substr(10)), doctors);
            } else if (line.find("[SERVICES]") == 0) {
                parse_services_section(in, std::stoul(line.substr(11)), services, doctors);
            } else if (line.find("[PATIENTS]") == 0) {
                parse_patients_section(in, std::stoul(line.substr(11)), patients);
            }
        }
        log("Загружено состояние системы из: " + filename);
    });
}

bool ClinicFileManager::generate_text_report(const std::string& report_filename,
                                             const Collection<Doctor*>& doctors,
                                             const Collection<Service*>& services,
                                             const Collection<Patient>& patients) {
    bool success = with_output_file(report_filename, std::ios::trunc, [&](std::ofstream& out) {
        out << "========================================================================\n"
            << "                 ОТЧЁТ О СОСТОЯНИИ СТОМАТОЛОГИЧЕСКОЙ КЛИНИКИ            \n"
            << "========================================================================\n\n";

        out << "1. ШТАТ СПЕЦИАЛИСТОВ (Всего: " << doctors.get_size() << "):\n";
        for (size_t i = 0; i < doctors.get_size(); ++i) out << "  " << (i + 1) << ". " << *doctors[i] << "\n";

        out << "\n2. ПРЕЙСКУРАНТ УСЛУГ (Всего: " << services.get_size() << "):\n";
        for (size_t i = 0; i < services.get_size(); ++i) out << "  " << (i + 1) << ". " << *services[i] << "\n";

        out << "\n3. КАРТОТЕКА ПАЦИЕНТОВ (Всего: " << patients.get_size() << "):\n";
        for (size_t i = 0; i < patients.get_size(); ++i) out << "  " << (i + 1) << ". " << patients[i] << "\n";
    });

    if (success) log("Сформирован отчёт: " + report_filename);
    return success;
}