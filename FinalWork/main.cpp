#include <iostream>
#include <vector>
#include <string>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {
    try {
        // 1. Инициализация конвертера для работы с JSON-файлами
        ConverterJSON converter;

        // 2. Считывание документов из путей, указанных в config.json
        std::vector<std::string> documents = converter.GetTextDocuments();

        // 3. Создание инвертированного индекса и запуск многопоточной индексации
        InvertedIndex index;
        index.UpdateDocumentBase(documents);

        // 4. Получение списка пользовательских поисковых запросов из requests.json
        std::vector<std::string> requests = converter.GetRequests();
        if (requests.empty()) {
            std::cout << "No requests found in requests.json or file is missing." << std::endl;
            return 0;
        }

        // 5. Инициализация поискового сервера и выполнение поиска
        SearchServer server(index);
        std::vector<std::vector<RelativeIndex>> search_results = server.search(requests);

        // 6. Трансформация результатов в формат для putAnswers {{doc_id, rank}, ...}
        std::vector<std::vector<std::pair<int, float>>> answers_to_save;
        for (const auto& query_res : search_results) {
            std::vector<std::pair<int, float>> current_query_answers;
            for (const auto& doc_info : query_res) {
                current_query_answers.push_back({static_cast<int>(doc_info.doc_id), doc_info.rank});
            }
            answers_to_save.push_back(current_query_answers);
        }

        // 7. Сохранение итоговых ответов в answers.json
        converter.putAnswers(answers_to_save);
        std::cout << "Search completed successfully. Results saved to answers.json." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Application terminated due to error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
