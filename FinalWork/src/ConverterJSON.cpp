#include "ConverterJSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::ifstream config_file("config.json");
    if (!config_file.is_open()) {
        std::cerr << "config file is missing" << std::endl;
        throw std::runtime_error("config file is missing");
    }

    nlohmann::json config_json;
    try {
        config_file >> config_json;
    } catch (...) {
        std::cerr << "config file is empty" << std::endl;
        throw std::runtime_error("config file is empty");
    }

    if (!config_json.contains("config")) {
        std::cerr << "config file is empty" << std::endl;
        throw std::runtime_error("config file is empty");
    }

    std::string engine_name = config_json["config"].value("name", "SearchEngine");
    std::cout << "Starting " << engine_name << std::endl;

    std::string version = config_json["config"].value("version", "0.1");
    if (version != "0.1") {
        std::cerr << "config.json has incorrect file version" << std::endl;
        throw std::runtime_error("config.json has incorrect file version");
    }

    std::vector<std::string> documents;
    if (config_json.contains("files")) {
        for (const auto& file_path : config_json["files"]) {
            std::ifstream doc_file(file_path.get<std::string>());
            if (!doc_file.is_open()) {
                std::cerr << "File not found: " << file_path << std::endl;
                continue;
            }
            std::string content((std::istreambuf_iterator<char>(doc_file)), std::istreambuf_iterator<char>());
            documents.push_back(content);
        }
    }
    return documents;
}

int ConverterJSON::GetResponsesLimit() {
    std::ifstream config_file("config.json");
    if (!config_file.is_open()) return 5;

    nlohmann::json config_json;
    try {
        config_file >> config_json;
        if (config_json.contains("config") && config_json["config"].contains("max_responses")) {
            return config_json["config"]["max_responses"].get<int>();
        }
    } catch (...) {}
    return 5; 
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream requests_file("requests.json");
    std::vector<std::string> requests;
    if (!requests_file.is_open()) {
        std::cerr << "requests.json is missing" << std::endl;
        return requests;
    }

    nlohmann::json requests_json;
    try {
        requests_file >> requests_json;
        if (requests_json.contains("requests")) {
            for (const auto& req : requests_json["requests"]) {
                requests.push_back(req.get<std::string>());
            }
        }
    } catch (...) {}
    return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
    nlohmann::json output_json;
    auto& answers_node = output_json["answers"];

    for (size_t i = 0; i < answers.size(); ++i) {
        char req_id[32];
        snprintf(req_id, sizeof(req_id), "request%03d", static_cast<int>(i + 1));

        if (answers[i].empty()) {
            answers_node[req_id]["result"] = "false";
        } else {
            answers_node[req_id]["result"] = "true";
            if (answers[i].size() == 1) {
                answers_node[req_id]["docid"] = answers[i][0].first;
                answers_node[req_id]["rank"] = answers[i][0].second;
            } else {
                for (const auto& p : answers[i]) {
    nlohmann::json relevance_item; 
    relevance_item["docid"] = p.first;
    relevance_item["rank"] = p.second;
    answers_node[req_id]["relevance"].push_back(relevance_item);
}
            }
        }
    }

    std::ofstream answers_file("answers.json", std::ios::trunc);
    if (answers_file.is_open()) {
        answers_file << output_json.dump(4);
    }
}
