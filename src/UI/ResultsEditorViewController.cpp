#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "UI/ResultsEditorViewController.hpp" 

#include "MainConfig.hpp"

#include "TMPro/TextMeshProUGUI.hpp"
#include "TMPro/TextMeshPro.hpp"

using namespace SpeecilTweaks::UI;
using namespace TMPro;
using namespace QuestUI;
using namespace QuestUI::BeatSaberUI;

DEFINE_TYPE(SpeecilTweaks::UI, ResultsEditorViewController);

void SpeecilTweaks::UI::ResultsEditorViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) 
{   if (!firstActivation) return;
    // creates the layout for the mod settings
    QuestUI::BeatSaberUI::CreateText(get_transform(), "Results Screen Editor", true, UnityEngine::Vector2(0.0, 47.5))->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->set_fontSize(9.0);

    UnityEngine::UI::VerticalLayoutGroup* layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_transform());

    TMPro::TextMeshProUGUI * text;
    TMPro::TextMeshProUGUI * text1;
    TMPro::TextMeshProUGUI * text2;
    TMPro::TextMeshProUGUI * text3;
    TMPro::TextMeshProUGUI * text4;
    TMPro::TextMeshProUGUI * text5;
    TMPro::TextMeshProUGUI * text6;
    TMPro::TextMeshProUGUI * space1;
    TMPro::TextMeshProUGUI * space2;
    // Creates a keyboard and sets the input to pauseText
    text2 -> set_alignment(TMPro::TextAlignmentOptions::Center);
    text1 = QuestUI::BeatSaberUI::CreateText(layout -> get_transform(), "If you pass a level...");
    text1 -> set_fontSize(5.0);
    BeatSaberUI::CreateStringSetting(layout -> get_transform(), StringW(getMainConfig().rText.GetName()), StringW(getMainConfig().rText.GetValue()), [](std::string rtext) {
      getMainConfig().rText.SetValue(rtext);
    });
    auto rBackColorPicker = BeatSaberUI::CreateColorPicker(layout -> get_transform(), "Pass Result Background Colour", getMainConfig().rBackColour.GetValue(), [](UnityEngine::Color color) {
      getMainConfig().rBackColour.SetValue(color, true);
    });
    space1 = QuestUI::BeatSaberUI::CreateText(layout -> get_transform(), "");
    text6 = QuestUI::BeatSaberUI::CreateText(layout -> get_transform(), "If you fail a level...");
    text6 -> set_fontSize(5.0);
    BeatSaberUI::CreateStringSetting(layout -> get_transform(), StringW(getMainConfig().rfText.GetName()), StringW(getMainConfig().rfText.GetValue()), [](std::string rftext) {
      getMainConfig().rfText.SetValue(rftext);
    });
    auto rfBackColorPicker = BeatSaberUI::CreateColorPicker(layout -> get_transform(), "Fail Result Background Colour", getMainConfig().rfBackColour.GetValue(), [](UnityEngine::Color color) {
      getMainConfig().rfBackColour.SetValue(color, true);
    });
  }
