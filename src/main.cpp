#include <iostream>
#include "../include/Collection.hpp"
#include "../include/Therapist.h"
#include "../include/Surgeon.h"
#include "../include/Orthodontist.h"
#include "../include/TherapeuticService.h"
#include "../include/SurgicalService.h"
#include "../include/OrthodonticService.h"
#include "../include/Patient.h"

#include "../exceptions/include_exp/InvalidDataException.h"
#include "../exceptions/include_exp/DoctorSpecialtyMismatchException.h"
#include "../exceptions/include_exp/DuplicatePatientException.h" // или DuplicateServiceException.h
#include "../exceptions/include_exp/ServiceNotFoundException.h"
#include "../exceptions/include_exp/IndexOutOfBoundsException.h"

int main() {
    std::cout << "=================================\n";
    std::cout << "   СТОМАТОЛОГИЧЕСКАЯ КЛИНИКА:\n";
    std::cout << "=================================\n\n";

    Collection<Doctor*> clinic_doctors;
    Doctor* therapist = new Therapist("Иванов И.И.", 10, 420);
    Doctor* surgeon   = new Surgeon("Петров П.П.", 15, 310);
    Doctor* orthodontist     = new Orthodontist("Сидорова А.А.", 7, 95);

    clinic_doctors.add(therapist);
    clinic_doctors.add(surgeon);
    clinic_doctors.add(orthodontist);

    std::cout << "Штат врачей клиники:\n" << clinic_doctors << "\n";

    Service* s_caries = new TherapeuticService("Лечение глубокого кариеса", 2800, 45, "16", false, therapist);
    Service* s_wisdom = new SurgicalService("Удаление зуба мудрости", 4500, 40, "Экстракция", surgeon);
    Service* s_braces = new OrthodonticService("Установка брекет-системы", 65000, 90, "Брекеты", "Керамика", orthodontist);

    Patient patient1("Смирнов Алексей Михайлович", true);   // С картой скидок
    Patient patient2("Ковалева Екатерина Сергеевна", false); // Без карты

    patient1 += s_caries;
    patient1 += s_wisdom;
    patient2 += s_braces;

    std::cout << "Информация о пациентах клиники:\n";
    std::cout << patient1 << "\n";
    std::cout << patient2 << "\n\n";

    std::cout << "========================================================================\n";
    std::cout << "========================================================================\n\n";

    std::cout << ">>> ИСКЛЮЧЕНИЕ 1: InvalidDataException (отрицательный стаж врача)\n";
    try {
        std::cout << "Попытка задать врачу стаж -5 лет...\n";
        therapist->set_experience(-5);
    } catch (const InvalidDataException& e) {
        std::cout << "[ПЕРЕХВАЧЕНО]: " << e.what() << "\n";
    }
    std::cout << "\n\n";

    std::cout << ">>> ИСКЛЮЧЕНИЕ 2: DoctorSpecialtyMismatchException (хирург на терапию)\n";
    try {
        std::cout << "Попытка назначить хирурга Петрова П.П. на пломбирование зуба...\n";
        s_caries->set_doctor(surgeon); // Ошибка: хирург не имеет допуска к терапии
    } catch (const DoctorSpecialtyMismatchException& e) {
        std::cout << "[ПЕРЕХВАЧЕНО]: " << e.what() << "\n";
    }
    std::cout << "\n\n";

    std::cout << ">>> ИСКЛЮЧЕНИЕ 3: Попытка повторного добавления уже назначенной услуги\n";
    try {
        std::cout << "Попытка повторно добавить услугу '" << s_caries->get_serve() << "' в карту пациента " << patient1.get_name() << "...\n";
        patient1 += s_caries; // Ошибка: услуга уже есть в плане лечения
    } catch (const ClinicException& e) {
        std::cout << "[ПЕРЕХВАЧЕНО]: " << e.what() << "\n";
    }
    std::cout << "\n\n";

    std::cout << ">>> ИСКЛЮЧЕНИЕ 4: ServiceNotFoundException (удаление несуществующей услуги)\n";
    Service* phantom_service = new SurgicalService("Пластика уздечки", 3500, 30, "Пластика", surgeon);
    try {
        std::cout << "Попытка удалить из карты пациента процедуру, которой там нет...\n";
        patient1 -= phantom_service;
    } catch (const ServiceNotFoundException& e) {
        std::cout << "[ПЕРЕХВАЧЕНО]: " << e.what() << "\n";
    }
    std::cout << "\n\n";

    std::cout << ">>> ИСКЛЮЧЕНИЕ 5: IndexOutOfBoundsException (выход за границы Collection<T>)\n";
    std::cout << "В штате клиники находится врачей: " << clinic_doctors.get_size() << " (индексы от 0 до "
              << clinic_doctors.get_size() - 1 << ")\n";
    try {
        std::cout << "Попытка обращения к врачу по индексу [10] через метод at()...\n";
        clinic_doctors.at(10); // Ошибка индексации
    } catch (const IndexOutOfBoundsException& e) {
        std::cout << "[ПЕРЕХВАЧЕНО]: " << e.what() << "\n";
    }
    std::cout << "\n\n";

    delete phantom_service;
    delete s_caries;
    delete s_wisdom;
    delete s_braces;
    for (size_t i = 0; i < clinic_doctors.get_size(); ++i) {
        delete clinic_doctors[i];
    }

    return 0;
}