#ifndef ANALIZE_H
#define ANALIZE_H

#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>

class Analizador
{
public:
  Analizador(const std::string &archivo) : archivo_(archivo) {
    this->analizar();
  }
  void analizar();
  void Show() {
    std::cout << "Archivo: " << archivo_ << std::endl;
    std::cout << "Contenido: " << contenido_ << std::endl;
  }
  void Salida();

  bool Header();
  bool Body();
  bool Html();

  void FindTags();
  void FindAttributes();
  void FindComments();

private:
  std::string archivo_;
  std::string contenido_;
  std::vector<std::string> texto_;
  std::vector<std::string> Tags_;
  std::vector<std::string> Atributos_;
  std::vector<std::string> Comments_;

  bool header_encontrado_;
  bool body_encontrado_;
  bool html_encontrado_;
};

#endif // ANALIZE_H