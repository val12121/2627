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
  void Salida() {
    std::cout << "PROGRAMA: " << archivo_ << std::endl;
    std::cout << "ESTRUCTURA: " << std::endl;
    std::cout << "HEAD: " << (header_encontrado_ ? "true" : "false") << std::endl;
    std::cout << "BODY: " << (body_encontrado_ ? "true" : "false") << std::endl;
    std::cout << "HTML: " << (html_encontrado_ ? "true" : "false") << std::endl;
  }

  bool Header() {
    std::regex header("<head>([\\s\\S]*)</head>");
    std::smatch match;
    if (std::regex_search(contenido_, match, header)) {
      header_encontrado_ = true;
      return true;
    } else {
      header_encontrado_ = false;
      return false; 
    }
  }
  bool Body() {
    std::regex body("<body>([\\s\\S]*)</body>");
    std::smatch match;
    if (std::regex_search(contenido_, match, body)) {
      body_encontrado_ = true;
      return true;
    } else {
      body_encontrado_ = false;
      return false; 
    }
  }
  bool Html() {
    std::regex html("<html>([\\s\\S]*)</html>");
    std::smatch match;
    if (std::regex_search(contenido_, match, html)) {
      html_encontrado_ = true;
      return true;
    } else {
      html_encontrado_ = false;
      return false; 
    }
  }
  private:
  std::string archivo_;
  std::string contenido_;
  std::vector<std::pair<std::string, std::string>> Tags;
  bool header_encontrado_;
  bool body_encontrado_;
  bool html_encontrado_;
};

#endif // ANALIZE_H