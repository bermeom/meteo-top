#ifndef DISPLAY_DATA_H_
#define DISPLAY_DATA_H_

#include <iostream>
#include <string>

#include "YamlCPP.hpp"

namespace METEO_TOP {

class DisplayOpenMeteoData {
   public:
    static bool show_full_data;

    static void show_data(size_t iterartion, std::string result) {
        std::cout << " ----------------------- " << iterartion
                  << " ----------------------- " << std::endl;
        YAML::Node node = YAML::Load(result);
        YAML::set_style_to_all_nodes(node, YAML::EmitterStyle::Block);
        if (DisplayOpenMeteoData::show_full_data) {
            std::cout << node << std::endl;
        } else {
            std::cout << node["current_weather"] << std::endl;
        }
    }
};
bool DisplayOpenMeteoData::show_full_data = false;

}  // namespace METEO_TOP
#endif  // PERIODIC_TASK_H_
