#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(MainConfig,
    CONFIG_VALUE(isEnabled, bool, "Enable Mod", true);
    CONFIG_VALUE(rText, std::string, "Results Text", "Well Done!");
    CONFIG_VALUE(rTextColour, UnityEngine::Color, "Colour", UnityEngine::Color(1.0, 1.0, 1.0, 1.0));
    CONFIG_VALUE(rBackColour, UnityEngine::Color, "Colour", UnityEngine::Color(1.0, 1.0, 1.0, 1.0));
    CONFIG_VALUE(EnablePlayButton, bool, "Enable Play Button", true);
    CONFIG_VALUE(aText, std::string, "Play Button Text", "Speecil!");



    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(isEnabled);
        CONFIG_INIT_VALUE(rText);
        CONFIG_INIT_VALUE(rTextColour);
        CONFIG_INIT_VALUE(rBackColour);
        CONFIG_INIT_VALUE(aText);

    )
)