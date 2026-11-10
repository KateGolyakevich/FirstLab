cmake_minimum_required(VERSION 3.31)
project(Lab_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_1 src/Patient.cpp
        src/Service.cpp
        src/main.cpp
        include/Doctor.h
        src/Doctor.cpp
        include/TherapeuticService.h
        include/SurgicalService.h
        include/OrthodonticService.h
        src/TherapeuticService.cpp
        src/SurgicalService.cpp
        src/OrthodonticService.cpp
        include/Therapist.h
        include/Surgeon.h
        include/Orthodontist.h
        src/Orthodontist.cpp
        src/Surgeon.cpp
        src/Therapist.cpp
        exceptions/include_exp/ClinicException.h
        exceptions/include_exp/InvalidDataException.h
        exceptions/include_exp/DoctorSpecialtyMismatchException.h
        exceptions/include_exp/DuplicatePatientException.h
        exceptions/include_exp/ServiceNotFoundException.h
        exceptions/include_exp/IndexOutOfBoundsException.h
        exceptions/src_exp/ClinicException.cpp
        exceptions/src_exp/InvalidDataException.cpp
        exceptions/src_exp/DoctorSpecialtyMismatchException.cpp
        exceptions/src_exp/DuplicatePatientException.cpp
        exceptions/src_exp/ServiceNotFoundException.cpp
        exceptions/src_exp/IndexOutOfBoundsException.cpp
)
