#pragma once
#include "UnityEngine/Color.hpp"
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(MainConfig,
    CONFIG_VALUE(rText, std::string, "Pass Results Text", "Well Done!");
    CONFIG_VALUE(rfText, std::string, "Fail Results Text", "You Suck.");
    CONFIG_VALUE(rBackColour, UnityEngine::Color, "Pass Colour", UnityEngine::Color(0.15, 0.15, 0.7, 1.0));
    CONFIG_VALUE(rfBackColour, UnityEngine::Color, "Fail Colour", UnityEngine::Color(1.0, 0.0, 0.0, 1.0));
    CONFIG_VALUE(EnablePlayButton, bool, "Enable the Play Button", true);
    CONFIG_VALUE(aText, std::string, "Play Button Text", "Speecil!");
    CONFIG_VALUE(EnablePracticeButton, bool, "Enable the Practice Button", true);
    CONFIG_VALUE(pText, std::string, "Practice Button Text", "Git Gud");
    CONFIG_VALUE(MenuButtonColour, UnityEngine::Color, "Menu Button Colour", UnityEngine::Color(0, 1.0, 1.0, 1.0));
    CONFIG_VALUE(DisableBombDebris, bool, "Disable Bomb Debris?", true);
    CONFIG_VALUE(EnablePMenuTweaks, bool, "Enable Pause Menu Tweaks?", true);
    CONFIG_VALUE(PMenuColour, UnityEngine::Color, "Pause Song Name Colour", UnityEngine::Color(0.1, 0.3, 1.0, 1.0));



    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(rText);
        CONFIG_INIT_VALUE(rfText);
        CONFIG_INIT_VALUE(rfBackColour);
        CONFIG_INIT_VALUE(rBackColour);
        CONFIG_INIT_VALUE(aText);
        CONFIG_INIT_VALUE(EnablePlayButton);
        CONFIG_INIT_VALUE(pText);
        CONFIG_INIT_VALUE(EnablePracticeButton);
        CONFIG_INIT_VALUE(MenuButtonColour);
        CONFIG_INIT_VALUE(DisableBombDebris);
        CONFIG_INIT_VALUE(EnablePMenuTweaks);
        CONFIG_INIT_VALUE(PMenuColour);

    )
)
