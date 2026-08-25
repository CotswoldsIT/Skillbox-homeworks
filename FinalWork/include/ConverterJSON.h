#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include "json.hpp"


    //Класс для работы с JSON-файлами

class ConverterJSON {
public:
    ConverterJSON() = default;

    
    //Метод получения содержимого файлов, перечисленных в config.json
    
    std::vector<std::string> GetTextDocuments();

    
    //Метод считывает поле max_responses для определения предела выдачи
    
    int GetResponsesLimit();

    
    //Метод получения запросов из файла requests.json
    
    std::vector<std::string> GetRequests();

    
    //Положить в файл answers.json результаты поисковых запросов
    
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};
