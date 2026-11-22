#include "../include/ClinicFileManager.h"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include <sstream>
#include <ctime>

Doctor* ClinicFileManager::find_doctor_by_name(const Collection<Doctor*>& doctors, const std::string& name) {
    for (size_t i = 0; i < doctors.get_size(); ++i) {
        if (doctors[i]->get_name() == name) return doctors[i];
    }
    return nullptr;
}

Service* ClinicFileManager::find_service_by_name(const Collection<Service*>& services, const std::string& name) {
    for (size_t i = 0; i < services.get_size(); ++i) {
        if (services[i]->get_serve() == name) return services[i];
    }
    return nullptr;
}

void ClinicFileManager::log_event(const std::string& log_filename, const std::string& message) {
    std::ofstream log_file(log_filename, std::ios::app);
    if (!log_file.is_open()) return;

    std::time_t now = std::time(nullptr);
    char buf[26];
    ctime_r(&now, buf);
    std::string time_str(buf);
    if (!time_str.empty() && time_str.back() == '\n') time_str.pop_back();

    log_file << "[" << time_str << "] " << message << "\n";
}

void ClinicFileManager::save_single_doctor(std::ofstream& out, Doctor* doc) {
    std::string type = doc->get_doctor_type();
    out << type << ";" << doc->get_name() << ";" << doc->get_experience() << ";";
    if (auto* t = dynamic_cast<Therapist*>(doc)) {
        out << t->get_filled_teeth();
    } else if (auto* s = dynamic_cast<Surgeon*>(doc)) {
        out << s->get_operations_count();
    } else if (auto* o = dynamic_cast<Orthodontist*>(doc)) {
        out << o->get_braces_patients();
    }
    out << "\n";
}

Doctor* ClinicFileManager::load_single_doctor(const std::string& line) {
    std::stringstream ss(line);
    std::string type, name, exp_str, spec_str;
    if (!std::getline(ss, type, ';') || !std::getline(ss, name, ';') ||
        !std::getline(ss, exp_str, ';') || !std::getline(ss, spec_str)) {
        return nullptr;
    }
    int exp = std::stoi(exp_str);
    int spec = std::stoi(spec_str);

    if (type == "Терапевт") return new Therapist(name, exp, spec);
    if (type == "Хирург")   return new Surgeon(name, exp, spec);
    if (type == "Ортодонт") return new Orthodontist(name, exp, spec);
    return nullptr;
}

void ClinicFileManager::save_single_service(std::ofstream& out, Service* srv) {
    std::string type = srv->get_serve_type();
    std::string doc_name = srv->get_doctor() ? srv->get_doctor()->get_name() : "NONE";
    out << type << ";" << srv->get_serve() << ";" << srv->get_cost() << ";"
        << srv->get_duration() << ";" << doc_name << ";";

    if (auto* t = dynamic_cast<TherapeuticService*>(srv)) {
        out << t->get_tooth_number() << ";" << (t->get_is_repeated() ? "1" : "0");
    } else if (auto* s = dynamic_cast<SurgicalService*>(srv)) {
        out << s->get_operation_type();
    } else if (auto* o = dynamic_cast<OrthodonticService*>(srv)) {
        out << o->get_correction_type() << ";" << o->get_correction_material();
    }
    out << "\n";
}

Service* ClinicFileManager::load_single_service(const std::string& line, const Collection<Doctor*>& doctors) {
    std::stringstream ss(line);
    std::string type, serve, cost_str, dur_str, doc_name;
    if (!std::getline(ss, type, ';') || !std::getline(ss, serve, ';') ||
        !std::getline(ss, cost_str, ';') || !std::getline(ss, dur_str, ';') ||
        !std::getline(ss, doc_name, ';')) return nullptr;

    int cost = std::stoi(cost_str);
    int dur = std::stoi(dur_str);
    Doctor* doc = (doc_name != "NONE") ? find_doctor_by_name(doctors, doc_name) : nullptr;

    if (type == "Терапия") {
        std::string tooth, rep_str;
        std::getline(ss, tooth, ';');
        std::getline(ss, rep_str);
        return new TherapeuticService(serve, cost, dur, tooth, rep_str == "1", doc);
    } else if (type == "Хирургия") {
        std::string op_type;
        std::getline(ss, op_type);
        return new SurgicalService(serve, cost, dur, op_type, doc);
    } else if (type == "Ортодонтия") {
        std::string corr_type, material;
        std::getline(ss, corr_type, ';');
        std::getline(ss, material);
        return new OrthodonticService(serve, cost, dur, corr_type, material, doc);
    }
    return nullptr;
}

// 6. Сохранение всего состояния
bool ClinicFileManager::save_system_state(const std::string& filename,
                                          const Collection<Doctor*>& doctors,
                                          const Collection<Service*>& services,
                                          const Collection<Patient>& patients) {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    out << "[DOCTORS] " << doctors.get_size() << "\n";
    for (size_t i = 0; i < doctors.get_size(); ++i) {
        save_single_doctor(out, doctors[i]);
    }

    out << "[SERVICES] " << services.get_size() << "\n";
    for (size_t i = 0; i < services.get_size(); ++i) {
        save_single_service(out, services[i]);
    }

    out << "[PATIENTS] " << patients.get_size() << "\n";
    for (size_t i = 0; i < patients.get_size(); ++i) {
        out << patients[i].get_name() << ";" << (patients[i].get_has_card() ? "1" : "0") << "\n";
    }

    log_event("journal.log", "Успешное сохранение состояния системы в файл: " + filename);
    return true;
}

bool ClinicFileManager::load_system_state(const std::string& filename,
                                          Collection<Doctor*>& doctors,
                                          Collection<Service*>& services,
                                          Collection<Patient>& patients) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    doctors.clear();
    services.clear();
    patients.clear();

    std::string line;
    while (std::getline(in, line)) {
        if (line.find("[DOCTORS]") == 0) {
            size_t count = std::stoul(line.substr(10));
            for (size_t i = 0; i < count && std::getline(in, line); ++i) {
                if (Doctor* d = load_single_doctor(line)) doctors.add(d);
            }
        } else if (line.find("[SERVICES]") == 0) {
            size_t count = std::stoul(line.substr(11));
            for (size_t i = 0; i < count && std::getline(in, line); ++i) {
                if (Service* s = load_single_service(line, doctors)) services.add(s);
            }
        } else if (line.find("[PATIENTS]") == 0) {
            size_t count = std::stoul(line.substr(11));
            for (size_t i = 0; i < count && std::getline(in, line); ++i) {
                std::stringstream ss(line);
                std::string p_name, card_str;
                if (std::getline(ss, p_name, ';') && std::getline(ss, card_str)) {
                    patients.add(Patient(p_name, card_str == "1"));
                }
            }
        }
    }

    log_event("journal.log", "Успешная загрузка состояния системы из файла: " + filename);
    return true;
}


bool ClinicFileManager::generate_text_report(const std::string& report_filename,
                                             const Collection<Doctor*>& doctors,
                                             const Collection<Service*>& services,
                                             const Collection<Patient>& patients) {
    std::ofstream out(report_filename);
    if (!out.is_open()) return false;

    out << "========================================================================\n";
    out << "                 ОТЧЁТ О СОСТОЯНИИ СТОМАТОЛОГИЧЕСКОЙ КЛИНИКИ            \n";
    out << "========================================================================\n\n";

    out << "1. ШТАТ СПЕЦИАЛИСТОВ (Всего: " << doctors.get_size() << "):\n";
    for (size_t i = 0; i < doctors.get_size(); ++i) {
        out << "  " << (i + 1) << ". " << *doctors[i] << "\n";
    }

    out << "\n2. ПРЕЙСКУРАНТ УСЛУГ (Всего: " << services.get_size() << "):\n";
    for (size_t i = 0; i < services.get_size(); ++i) {
        out << "  " << (i + 1) << ". " << *services[i] << "\n";
    }

    out << "\n3. КАРТОТЕКА ПАЦИЕНТОВ (Всего: " << patients.get_size() << "):\n";
    for (size_t i = 0; i < patients.get_size(); ++i) {
        out << "  " << (i + 1) << ". " << patients[i] << "\n";
    }

    out << "\n========================================================================\n";
    out << "Отчёт сформирован автоматически программным комплексом клиники.\n";

    log_event("journal.log", "Сформирован текстовый аналитический отчёт: " + report_filename);
    return true;
}