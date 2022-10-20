#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(MainConfig,
    CONFIG_VALUE(rText, std::string, "Pass Results Text", "Well Done!");
    CONFIG_VALUE(rfText, std::string, "Fail Results Text", "You Suck.");
    CONFIG_VALUE(rBackColour, UnityEngine::Color, "Colour", UnityEngine::Color(1.0, 1.0, 1.0, 1.0));
    CONFIG_VALUE(rfBackColour, UnityEngine::Color, "Colour", UnityEngine::Color(1.0, 1.0, 1.0, 1.0));
    CONFIG_VALUE(EnablePlayButton, bool, "Enable Play Button", true);
    CONFIG_VALUE(aText, std::string, "Play Button Text", "Speecil!");



    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(rText);
        CONFIG_INIT_VALUE(rfBackColour);
        CONFIG_INIT_VALUE(rBackColour);
        CONFIG_INIT_VALUE(aText);
        CONFIG_INIT_VALUE(EnablePlayButton);
    )
)