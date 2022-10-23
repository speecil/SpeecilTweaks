#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "UI/MiscSettingsViewController.hpp"

#include "MainConfig.hpp"

#include "TMPro/TextMeshProUGUI.hpp"
#include "TMPro/TextMeshPro.hpp"

using namespace SpeecilTweaks::UI;
using namespace TMPro;
using namespace QuestUI;
using namespace QuestUI::BeatSaberUI;

DEFINE_TYPE(SpeecilTweaks::UI, MiscSettingsViewController);

void SpeecilTweaks::UI::MiscSettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) 
{   if (!firstActivation) return;
    // creates the layout for the mod settings
    QuestUI::BeatSaberUI::CreateText(get_transform(), "Miscellanous Tweaks", true, UnityEngine::Vector2(0.0, 47.5))->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->set_fontSize(9.0);
    TMPro::TextMeshProUGUI * text;
    UnityEngine::UI::VerticalLayoutGroup* layout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
    auto rBackColorPicker = BeatSaberUI::CreateColorPicker(layout -> get_transform(), "Menu Button Text Colour", getMainConfig().MenuButtonColour.GetValue(), [](UnityEngine::Color color) {
      getMainConfig().MenuButtonColour.SetValue(color, true);
    });
    AddConfigValueToggle(layout->get_transform(), getMainConfig().DisableBombDebris);
    text = QuestUI::BeatSaberUI::CreateText(layout -> get_transform(), "More Features coming soon!");
    text -> set_fontSize(7.0);
    text -> set_alignment(TMPro::TextAlignmentOptions::Center);
}