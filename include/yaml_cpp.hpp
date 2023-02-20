#ifndef YAML_CPP_H_
#define YAML_CPP_H_

#include <yaml-cpp/yaml.h>

namespace YAML {

void set_style_to_all_nodes(Node &node, EmitterStyle::value style);

}  // namespace YAML

#endif  // YAML_CPP_H_
