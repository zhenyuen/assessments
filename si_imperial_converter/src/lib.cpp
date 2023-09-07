#include "lib.hpp"

#include <bits/stdc++.h>

#include "globals.hpp"

Data::Data() {
    // Populate prefix map
    prefixes["p"] = 1e-12;
    prefixes["n"] = 1e-9;
    prefixes["mu"] = 1e-6;
    prefixes["m"] = 1e-3;
    prefixes["c"] = 1e-2;
    prefixes["K"] = 1e3;
    prefixes["M"] = 1e6;
    prefixes["G"] = 1e9;
    prefixes["T"] = 1e12;

    // Populate si units
    si_units.insert("m");  // meter
    si_units.insert("s");  // second

    // Populate imperial units
    imperial_units.insert("inch");
    imperial_units.insert("feet");
    imperial_units.insert("mile");
}

std::pair<double, std::string> Data::parse_unit(
    std::string const &input) const {
    if (imperial_units.find(input) != imperial_units.end()) return {1, input};
    // input is in SI, first letter would be prefix;
    // assume every base unit is only represented by the last character
    std::string prefix = input.substr(0, input.size() - 1);

    double multiplier =
        prefixes.find(prefix) == prefixes.end() ? 1 : prefixes.at(prefix);

    if (_DEBUG) {
        std::cout << "prefix: " << prefix << std::endl;
        std::cout << "multiplier: " << multiplier << std::endl;
    }

    return {multiplier, std::string(1, input.back())};
}

void Data::parse() {
    std::string buffer;

    while (std::getline(std::cin, buffer)) {
        std::stringstream ss(buffer);
        std::string start_raw, end_raw;
        std::string _;  // to consume unused strings

        if (!(ss >> x)) {
            throw std::runtime_error("invalid input x");
        };
        if (!(ss >> start_raw)) {
            throw std::runtime_error("invalid starting unit");
        };
        ss >> _;  // to consume equal sign;
        ss >> _;  // to consume ?;
        if (!(ss >> end_raw)) {
            throw std::runtime_error("invalid ending unit");
        };

        auto [a, b] = parse_unit(start_raw);
        x_prefix = a, start = b;

        auto [c, d] = parse_unit(end_raw);
        y_prefix = c, end = d;

        if (_DEBUG) {
            std::cout << "multiplier: " << Data::x_prefix << std::endl;
        }
    }
}

Graph::Graph(Data &d) {
    // Define relationships between nodes
    // Conversion from google
    adj["m"]["mile"] = 1. / 1600;
    adj["m"]["feet"] = 3.28084;
    adj["m"]["inch"] = 39.3701;
    adj["mile"]["m"] = 1600;
    adj["feet"]["m"] = 1. / 3.28084;
    adj["inch"]["m"] = 1. / 39.3701;
    adj["s"] = {};  // empty for now;
}

std::vector<double> Graph::build(std::string start, std::string end) {
    if (cache.find(start) != cache.end() &&
        cache[start].find(end) != cache[start].end())
        return cache[start][end];
    if (start == end) return {1};
    std::vector<double> sequence;

    std::queue<std::string> q;
    q.push(start);

    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> parent;  // for backtracking
    visited.insert(start);

    while (!q.empty()) {
        auto node = std::move(q.front());
        q.pop();
        if (node == end) {
            // backtrack
            do {
                std::cout << node << std::endl;

                auto p = parent[node];
                std::cout << p << " " << adj[p][node] <<std::endl;
                sequence.push_back(adj[p][node]);
                node = p;
            } while (node != start);
            return cache[start][end] = sequence;
        }

        for (auto [b, _] : adj[node]) {
            if (visited.find(b) != visited.end()) continue;
            visited.insert(b);
            parent[b] = node;
            q.push(b);
        }
    }
    return cache[start][end] = {};  // empty indicates invalid conversion
}

double Graph::process(std::vector<double> const &sequence, Data &data) const {
    auto result = data.get_x();
    
    for (auto s: sequence) {
        result *= s;
    }
    std::cout << result << std::endl;
    result *= data.get_x_prefix();
    result /= data.get_y_prefix();
    return result;
}


