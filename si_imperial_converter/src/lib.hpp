#ifndef LIB_HPP
#define LIB_HPP

#include <bits/stdc++.h>

class Data {
   private:
    std::unordered_set<std::string> si_units;
    std::unordered_set<std::string> imperial_units;
    std::unordered_map<std::string, double> prefixes;

    double x_prefix;
    double y_prefix;
    double x;
    std::string start;
    std::string end;

    std::pair<double, std::string> parse_unit(std::string const &) const;

   public:
    Data();
    void parse();

    std::string const &get_start() const { return start; };
    std::string const &get_end() const { return end; };
    double const &get_x_prefix() const { return x_prefix; };
    double const &get_y_prefix() const { return y_prefix; };
    double const &get_x() const { return x; };
    std::unordered_map<std::string, double> const &get_prefixes() const { return prefixes; };
    std::unordered_set<std::string> const &get_si_units() const { return si_units; };
    std::unordered_set<std::string> const &get_imperial_units() const { return imperial_units; };
};

class Graph {
   private:
    std::unordered_map<std::string, std::unordered_map<std::string, double>> adj;
    std::unordered_map<std::string,
                       std::unordered_map<std::string, std::vector<double>>>
        cache;

   public:
    Graph(Data &data);
    std::vector<double> build(std::string start, std::string end); // no const as we are modiyfing cache
    double process(std::vector<double> const &sequence, Data &data) const;
};

#endif