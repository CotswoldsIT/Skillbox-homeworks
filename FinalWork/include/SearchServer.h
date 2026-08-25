#pragma once

#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "InvertedIndex.h"

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && std::abs(rank - other.rank) < 1e-5f);
    }
};

class SearchServer {
public:
    SearchServer(InvertedIndex& idx) : _index(idx) {}

    /**
    * Метод обработки поисковых запросов
    */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex& _index;
};
