#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>

/**
 * @class filehandler
 * @brief Klasa do obsługi odczytu i zapisu do plików.
 * @author Bartosz Biesiada
*/
class filehandler {
public:
    /**
     * @brief Konstruktor otwierający określony plik do odczytu.
     * @param filename Nazwa pliku do otwarcia.
    */
    filehandler(const std::string& filename);

    /**
     * @brief Odczytuje zawartość pliku i zapisuje ją w podanym ciągu znaków.
     * @param text Ciąg znaków do zapisania zawartości pliku
    */
    void read(std::string &text);

    /**
     * @brief Zamyka plik, jeśli jest otwarty.
    */
    void close();

    /**
     * @brief Zapisuje określoną zawartość do pliku. Tworzy plik, jeśli nie istnieje i nadpisuje go, jeśli istnieje.
     * @param filename Nazwa pliku do zapisu. 
     * @param text Zawartość do zapisania w pliku.
    */
    void write(const std::string& filename, const std::string& text);

private:
    std::ifstream file;
};

#endif
