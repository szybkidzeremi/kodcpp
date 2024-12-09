#include "filehandler.h"

filehandler::filehandler(const std::string& filename) : file(filename) {
	if (!file.is_open()) {
		std::cerr << "Błąd odczytu pliku: " << filename << std::endl;
	}
}

void filehandler::read(std::string& text) {
	std::string line;
	while (std::getline(file, line)) {
		text += line + "\n";
	}
}

void filehandler::close() {
	if (file.is_open()) {
		file.close();
#ifdef DEBUG_ENABLED
		std::cout << "plik zamknięty." << std::endl;
#endif
	}
}

void filehandler::write(const std::string& filename, const std::string& text) {
	std::ofstream outfile(filename);
	if (!outfile.is_open()) {
		std::cerr << "Błąd odczytu pliku: " << filename << std::endl;
		return;
	}
	outfile << text;
	outfile.close();
#ifdef DEBUG_ENABLED
	std::cout << "plik zapisany." << std::endl;
#endif
}
