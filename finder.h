#ifndef FINDER_H
#define FINDER_H

#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>

/**
 * @class finder
 * @brief Klasa finder służąca do szukania funkcji, zmiennych, itd. w plikach źródłowych C++.
 * @author Bartosz Biesiada
 */
class finder {
public:
    /**
     * @brief Konstruktor klasy finder.
     * @author Bartosz Biesiada
     * @param code Kod źródłowy jako string.
     */
    finder(const std::string& code);

    /**
     * @brief Znajduje funkcje w kodzie źródłowym.
     * @return std::string Lista znalezionych funkcji.
     */
    std::string find_functions() const;

    /**
     * @brief Znajduje zmienne lokalne w funkcjach w kodzie źródłowym.
     * @return std::string Lista zmiennych lokalnych w funkcjach.
     */
    std::string find_local_variables() const;

    /**
     * @brief Znajduje wywołane funkcje w kodzie źródłowym.
     * @return std::string Lista wywołanych funkcji.
     */
    std::string find_called_functions() const;

    /**
     * @brief Znajduje wywołania danej funkcji w innych funkcjach w kodzie źródłowym.
     * @param function_name Nazwa funkcji do wyszukania.
     * @return std::string Lista funkcji, w których dana funkcja jest wywoływana.
     */
    std::string find_function_calls_in_functions(const std::string& functionName) const;

    /**
     * @brief Znajduje zmienne o tej samej nazwie w różnych funkcjach w kodzie źródłowym.
     * @return std::string Lista zmiennych o tych samych nazwach znalezionych w kilku funkcjach.
     */
    std::string find_duplicate_variables() const;

    /**
     * @brief Znajduje zmienne danego typu w kodzie źródłowym.
     * @param type Typ zmiennej do wyszukania.
     * @return std::string Lista zmiennych danego typu.
     */
    std::string find_variables_by_type(const std::string& type) const;
private:
    std::string code;
};

#endif
