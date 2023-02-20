#include "YamlCPP.hpp"

#include <queue>

namespace YAML {

void set_style_to_all_nodes(YAML::Node &node, YAML::EmitterStyle::value style) {
    std::queue<YAML::iterator> q;
    YAML::iterator current_it;

    node.SetStyle(style);
    for (YAML::iterator it = node.begin(); it != node.end(); ++it) {
        if (it->second.IsMap()) {
            q.push(it);
            it->second.SetStyle(style);
        } else if (it->second.IsSequence()) {
            it->second.SetStyle(style);
        }
    }

    while (!q.empty()) {
        current_it = q.front();
        q.pop();
        if (current_it->second.IsMap()) {
            for (YAML::iterator it = current_it->second.begin();
                 it != current_it->second.end(); ++it) {
                if (it->second.IsMap()) {
                    q.push(it);
                    it->second.SetStyle(style);
                } else if (it->second.IsSequence()) {
                    it->second.SetStyle(style);
                }
            }
            // return;
        }
    }
}

}  // namespace YAML
