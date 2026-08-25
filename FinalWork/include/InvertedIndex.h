#pragma once

#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <sstream>
#include <algorithm>

struct Entry {
    size_t doc_id;
    size_t count;

    // Оператор для юнит-тестов (строго по ТЗ)
    bool operator==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
public:
    InvertedIndex() = default;

    /**
    * Обновить или заполнить базу документов, по которой будем совершать поиск
    * @param input_docs содержимое документов
    */
    void UpdateDocumentBase(std::vector<std::string> input_docs);

    /**
    * Метод определяет количество вхождений слова word в загруженной базе документов
    * @param word слово, частоту вхождений которого необходимо определить
    * @return возвращает подготовленный список с частотой слов
    */
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::vector<std::string> docs; // Список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // Частотный словарь
    std::mutex dict_mutex; // Мьютекс для безопасного многопоточного заполнения словаря
};
