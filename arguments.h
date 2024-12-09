#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>

/**
 * @class arguments
 * @brief Klasa arguments służąca do odczytu argumentów przekazanych do programu.
 * @author Bartosz Biesiada
 */
class arguments {
public:
    /**
     * @brief Konstruktor klasy arguments. Parsuje argumenty przekazane do programu.
     * @param argc Liczba argumentów przekazanych do programu.
     * @param argv Tablica argumentów przekazanych do programu.
     */
    arguments(int argc, char* argv[]);

    /**
     * @brief Zwraca nazwę pliku wejściowego.
     * @return std::string Nazwa pliku wejściowego.
     */
    std::string get_input() const;

    /**
     * @brief Zwraca nazwę pliku wyjściowego.
     * @return std::string Nazwa pliku wyjściowego.
     */
    std::string get_output() const;

    /**
     * @brief Sprawdza, czy powinny być wyszukiwane zmienne lokalne.
     * @return true Jeśli powinny być wyszukiwane zmienne lokalne.
     * @return false Jeśli nie powinny być wyszukiwane zmienne lokalne.
     */
    bool find_local_variables() const;

    /**
     * @brief Sprawdza, czy powinny być wyszukiwane wywołane funkcje.
     * @return true Jeśli powinny być wyszukiwane wywołane funkcje.
     * @return false Jeśli nie powinny być wyszukiwane wywołane funkcje.
     */
    bool find_called_functions() const;

    /**
     * @brief Sprawdza, czy powinny być wyszukiwane zmienne o tej samej nazwie w różnych funkcjach.
     * @return true Jeśli powinny być wyszukiwane zmienne o tej samej nazwie w różnych funkcjach.
     * @return false Jeśli nie powinny być wyszukiwane zmienne o tej samej nazwie w różnych funkcjach.
     */
    bool find_duplicate_variables() const;

    /**
     * @brief Zwraca nazwę funkcji do wyszukania jej wywołań.
     * @return std::string Nazwa funkcji.
     */
    std::string find_function_calls() const;

    /**
     * @brief Zwraca typ zmiennej do wyszukania jej wystąpień.
     * @return std::string Typ zmiennej.
     */
    std::string find_variables_by_type() const;

private:
    /* Plik wejściowy i wyjściowy */
    std::string input_file;
    std::string output_file;
    
    /* Argumenty */
    bool local_variables;
    bool called_functions;
    bool duplicate_variables;
    std::string function_calls;
    std::string variables_by_type;

    /**
     * @brief Parsuje argumenty wiersza poleceń.
     * @param argc Liczba argumentów wiersza poleceń.
     * @param argv Tablica argumentów wiersza poleceń.
    */
    void parse(int argc, char* argv[]);
};

#endif
