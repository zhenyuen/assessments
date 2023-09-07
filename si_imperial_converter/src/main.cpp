#include <bits/stdc++.h>
#include <exception>
#include "globals.hpp"
#include "lib.hpp"


int main() {

    try {
        // ============================= PARSE =============================
        Data data;
        data.parse();

        if (_DEBUG) {
            std::cout << data.get_start() << std::endl;
            std::cout << data.get_end() << std::endl;
            std::cout << data.get_x_prefix() << std::endl;
            std::cout << data.get_y_prefix() << std::endl;
        }
        // ========================= DEFINE GRAPH ==========================
        Graph g(data);

        if (_DEBUG) {
            auto t = g.build("m", "mile");
            for (auto w: t) { std::cout << w << " ";};
            std::cout << std::endl;

            t = g.build("s", "s");
            for (auto w: t) { std::cout << w << " ";};
            std::cout << std::endl;

            t = g.build("s", "m");
            for (auto w: t) { std::cout << w << " ";};
            std::cout << std::endl;

            t = g.build("mile", "inch");
            for (auto w: t) { std::cout << w << " ";};
            std::cout << std::endl;

            t = g.build("m", "inch");
            for (auto w: t) { std::cout << w << " ";};
            std::cout << std::endl;
        }

        // ========================= DEFINE COMPUTATIONAL GRAPH ==========================
        auto seq = g.build(data.get_start(), data.get_end());
        if (seq.empty()) throw std::runtime_error("invalid unit conversion");

        // Execute and print converted quantity to stdout;
        std::cout << g.process(seq, data) << std::endl;
        
    } catch(std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}




