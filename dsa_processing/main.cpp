#include <bits/stdc++.h>
#include <exception>


class data {
   private:
    struct job {
        int id;
        int duration;
        int next_id;
        job(int id_, int duration_, int next_id_)
            : id(id_), duration(duration_), next_id(next_id_){};
    };

    std::vector<job> jobs;

   public:
    bool parse() {
        std::string s;
        while (std::getline(std::cin, s)) {
            std::stringstream ss(s);
            int a, b, c;
            char comma;
            if (!(ss >> a)) {
                std::cout << "invalid arg: id" << std::endl;
                return false;
            };
            if (!(ss >> comma)) {
                std::cout << "invalid arg: comma" << std::endl;
                return false;
            };
            if (!(ss >> b)) {
                std::cout << "invalid arg: duration" << std::endl;
                return false;
            };
            if (!(ss >> comma)) {
                std::cout << "invalid arg: comma" << std::endl;
                return false;
            };
            if (!(ss >> c)) {
                std::cout << "invalid arg: next_id" << std::endl;
                return false;
            };
            jobs.push_back(job(a, b, c));
        }
        return true;
    }

    std::vector<job> const &get_all() const {
        // return constant reference as we do not want to return a copy
        return jobs;
    }
};

class process {
   private:
    struct node {
        int id;
        int duration;
        node() {};
        node(int id_) : id(id_), duration(-1){};
        node(int id_, int duration_) : id(id_), duration(duration_) {}
        size_t operator()(node const &a) const { return a.id; }
    };

    std::unordered_map<int, std::vector<int>> adj;
    std::unordered_map<int, std::vector<int>> cache;
    std::unordered_map<int, node> nodes; // use a map to unique keys to nodes

   public:
    process(data const &data_) {
        // from data, we identify that the start id form a distinct node;
        for (auto const &d : data_.get_all()) {
            if (d.id == 0) throw std::runtime_error("0 node found.");
            if (nodes.find(d.id) == nodes.end()) {
                nodes[d.id] = node(d.id, d.duration);
                adj[d.id] = {}; // initialize adj list
            } else
                nodes[d.id].duration = d.duration;

            if (d.next_id != 0 && nodes.find(d.next_id) == nodes.end())
                nodes[d.next_id] = node(d.next_id);
        }

        // valide all nodes are populated -- ensure no durations are -1
        for (auto const &[k, v]: nodes) {
            if (v.duration == -1) throw std::runtime_error("node not found.");
            // std::cout<< k << std::endl;
        }

        // build adj list
        for (auto const &d : data_.get_all()) {
            if (d.next_id == 0) continue; // 0 is not a node;
            adj[d.id].push_back(d.next_id);
        }
    };

    std::vector<std::vector<int>> build() {
        // perform a topological sort
        std::unordered_set<int> visited;
        std::unordered_set<int> visiting;
        std::vector<std::vector<int>> sequences;

        auto dfs = [&](auto &&dfs, int node) -> std::vector<int> {
            if (visited.find(node) != visited.end()) return cache[node];
            if (visiting.find(node) != visiting.end()) {
                throw std::runtime_error("loop found.");
            }
            visiting.insert(node);

            std::vector<int> child;
            for (auto b : adj[node]) {
                child = dfs(dfs, b);
            }
            child.push_back(node);
            visiting.erase(node);
            visited.insert(node);
            return cache[node] = child;
        };

        for (auto const &[k, v] : adj) {
            // for (auto v: visited) std::cout << v;
            // std::cout << std::endl;
            if (visited.find(k) != visited.end()) continue;
            // std::cout<< k << std::endl;
            std::vector<int> child = dfs(dfs, k);
            
            if (child.empty()) return {};
            sequences.push_back(std::move(child));
        }
        return sequences;
    }

    void execute(std::vector<std::vector<int>> &sequences) {
        for (auto const &s : sequences) {
            long long total = 0;
            double average = 0;
            int count = 0;
            for (auto const &id : s) {
                auto const &node = nodes[id];
                count++;
                total += node.duration;
                average = total / count;
            }
            std::cout << "-" << std::endl;
            std::cout << "start: " << s.back() << std::endl;
            std::cout << "end: " << s.front() << std::endl;
            std::cout << "total: " << total << std::endl;
            std::cout << "avg: " << average << std::endl;
            std::cout << "count: " << count << std::endl;
        }
        std::cout << "-" << std::endl;
    }
};

int main() {
    // Parse
    data d;
    if (!d.parse()) {
        std::cerr << "parse error." << std::endl;
        return 1;           // parse error
    }
    if (d.get_all().empty()) {
        std::cerr << "nothing to process." << std::endl;
        return 123;  // nothing to build;
    }

    // Build graph
    try {
        process p(d);
        // Build computation sequence
        auto seq = p.build();       // no arguments needed cause we only have one
                                    // operation -- forming chains
        if (seq.empty()) {
            std::cerr << "computation graph invalid." << std::endl;
            return 1;  // computation graph invalid;
        }

        // Execute sequence
        p.execute(seq);


    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    

    return 0;
}