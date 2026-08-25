#include "InvertedIndex.h"
#include <thread>

// Функция для очистки слова от знаков препинания и приведения к нижнему регистру
std::string cleanWord(const std::string& word) {
    std::string result = "";
    for (char ch : word) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            result += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    return result;
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    docs = input_docs;
    freq_dictionary.clear();

    std::vector<std::thread> threads;
    
    // Временная структура для накопления частот по каждому документу
    // чтобы минимизировать блокировку общего мьютекса
    for (size_t doc_idx = 0; doc_idx < docs.size(); ++doc_idx) {
        threads.emplace_back([this, doc_idx]() {
            std::map<std::string, size_t> local_counts;
            std::stringstream ss(docs[doc_idx]);
            std::string raw_word;

            // Разбор текста документа на отдельные слова
            while (ss >> raw_word) {
                std::string word = cleanWord(raw_word);
                if (!word.empty()) {
                    local_counts[word]++;
                }
            }

            // Синхронизация записи локальных результатов в общий частотный словарь
            std::lock_guard<std::mutex> lock(dict_mutex);
            for (const auto& [word, count] : local_counts) {
                freq_dictionary[word].push_back(Entry{doc_idx, count});
            }
        });
    }

    // Ожидание завершения работы всех потоков индексации
    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    
    for (auto& [word, entries] : freq_dictionary) {
        std::sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b) {
            return a.doc_id < b.doc_id;
        });
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::string clean = cleanWord(word);
    auto it = freq_dictionary.find(clean);
    if (it != freq_dictionary.end()) {
        return it->second;
    }
    return {}; // Если слова нет в базе, возвращаем пустой вектор 
}
