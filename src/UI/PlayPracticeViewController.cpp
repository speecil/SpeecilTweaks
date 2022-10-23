#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "UI/PlayPracticeViewController.hpp" 

#include "MainConfig.hpp"

#include "TMPro/TextMeshProUGUI.hpp"
#include "TMPro/TextMeshPro.hpp"

using namespace SpeecilTweaks::UI;
using namespace TMPro;
using namespace QuestUI;

DEFINE_TYPE(SpeecilTweaks::UI, PlayPracticeViewController);

void SpeecilTweaks::UI::PlayPracticeViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) 
{   if (!firstActivation) return;
    
    TMPro::TextMeshProUGUI * text;
    TMPro::TextMeshProUGUI * text1;
    TMPro::TextMeshProUGUI * text2;
    TMPro::TextMeshProUGUI * text3;
    TMPro::TextMeshProUGUI * text4;
    TMPro::TextMeshProUGUI * text5;
    TMPro::TextMeshProUGUI * text6;
    TMPro::TextMeshProUGUI * space1;
    TMPro::TextMeshProUGUI * space2;
    UnityEngine::GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
    text3 = QuestUI::BeatSaberUI::CreateText(container -> get_transform(), "Play and Practice Button Editor");
    text3 -> set_alignment(TMPro::TextAlignmentOptions::Center);
    text3 -> set_fontSize(9.0);
    space1 = QuestUI::BeatSaberUI::CreateText(container -> get_transform(), "");
    AddConfigValueToggle(container->get_transform(), getMainConfig().EnablePlayButton);
    AddConfigValueStringSetting(container->get_transform(), getMainConfig().aText);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AddConfigValueToggle(container->get_transform(), getMainConfig().EnablePracticeButton);
    AddConfigValueStringSetting(container->get_transform(), getMainConfig().pText);

    text4 = QuestUI::BeatSaberUI::CreateText(container -> get_transform(), "Message speecil#5350 on discord if there are any issues");
    text4 -> set_alignment(TMPro::TextAlignmentOptions::Center);
    text5 = QuestUI::BeatSaberUI::CreateText(container -> get_transform(), "Speecil Tweaks 0.2.0");
    text5 -> set_alignment(TMPro::TextAlignmentOptions::Center);
    text5 -> set_fontSize(5.0);
    text5 -> set_color(UnityEngine::Color::get_green());
  }
