#include "main.hpp"

#include "MainConfig.hpp"

#include "extern/includes/bs-utils/shared/utils.hpp"

#include "questui/shared/QuestUI.hpp"

#include "GlobalNamespace/ResultsViewController.hpp"

#include "GlobalNamespace/LevelCompletionResults.hpp"

#include "GlobalNamespace/StandardLevelDetailView.hpp"

#include "HMUI/ImageView.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

#include "UnityEngine/GameObject.hpp"

#include "UnityEngine/Transform.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace QuestUI;
using namespace custom_types;
using namespace QuestUI::BeatSaberUI;
using namespace TMPro;

DEFINE_CONFIG(MainConfig);

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be removed if those are in use
Configuration & getConfig() {
  static Configuration config(modInfo);
  return config;
}

// Returns a logger, useful for printing debug messages
Logger & getLogger() {
  static Logger * logger = new Logger(modInfo);
  return *logger;
}
// Creates a settings menu
void DidActivate(HMUI::ViewController * self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
  if (firstActivation) {
    // creates the container for the mod settings
    UnityEngine::GameObject * container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self -> get_transform());
    getLogger().info("created settings menu");
    TMPro::TextMeshProUGUI * text;
    TMPro::TextMeshProUGUI * text1;
    TMPro::TextMeshProUGUI * text2;
    TMPro::TextMeshProUGUI * text3;
    // creates a toggle for the mod
    CreateToggle(container -> get_transform(), "Enable Speecil Tweaks", getMainConfig().isEnabled.GetValue(), [](bool value) {
      getMainConfig().isEnabled.SetValue(value);
      getLogger().info("Toggled speecil tweaks Mod");

    });
    // Splits the UI to seperate mod toggle and the editing of text
    QuestUI::BeatSaberUI::CreateText(container -> get_transform(), "_______________________________________________");
    // Creates a keyboard and sets the input to pauseText
    text2 = QuestUI::BeatSaberUI::CreateText(container -> get_transform(), "Results Screen Editor");
    text2 -> set_alignment(TMPro::TextAlignmentOptions::Center);
    BeatSaberUI::CreateStringSetting(container -> get_transform(), StringW(getMainConfig().rText.GetName()), StringW(getMainConfig().rText.GetValue()), [](std::string rtext) {
      getMainConfig().rText.SetValue(rtext);
    });
    auto rBackColorPicker = BeatSaberUI::CreateColorPicker(container -> get_transform(), "Results Background Colour", getMainConfig().rBackColour.GetValue(), [](UnityEngine::Color color) {
      getMainConfig().rBackColour.SetValue(color, true);
    });
    QuestUI::BeatSaberUI::CreateText(container -> get_transform(), "_______________________________________________");
    text3 = QuestUI::BeatSaberUI::CreateText(container -> get_transform(), "Play Button Editor");
    text3 -> set_alignment(TMPro::TextAlignmentOptions::Center);
    CreateToggle(container -> get_transform(), "Enable the play button", getMainConfig().isEnabled.GetValue(), [](bool value) {
      getMainConfig().EnablePlayButton.SetValue(value);
      getLogger().info("Toggled speecil tweaks Mod");

    });
    BeatSaberUI::CreateStringSetting(container -> get_transform(), StringW(getMainConfig().aText.GetName()), StringW(getMainConfig().aText.GetValue()), [](std::string atext) {
      getMainConfig().aText.SetValue(atext);

    });
  }
}
// allows for the results banner and text to be changed
static void setResultUI(UnityEngine::GameObject * clearedBannerGo) {

  clearedBannerGo -> GetComponentsInChildren < TextMeshProUGUI * > ()[0] -> set_text(il2cpp_utils::newcsstr(getMainConfig().rText.GetValue()));
  clearedBannerGo -> GetComponentsInChildren < HMUI::ImageView * > ()[0] -> set_color(getMainConfig().rBackColour.GetValue());

}
// allows for the play button text to be changed
static void setActionButton(UnityEngine::UI::Button * actionButton) {

  actionButton->GetComponentsInChildren<TextMeshProUGUI*>()[0]->set_text(il2cpp_utils::newcsstr(getMainConfig().aText.GetValue()));

}
// grabs the play button and if the mod is enabled, it then checks if the user wants the play button to exist, then changes the text of the play button to what the user wants
MAKE_HOOK_MATCH(LevelUIHook, & GlobalNamespace::StandardLevelDetailView::RefreshContent, void, GlobalNamespace::StandardLevelDetailView *
  self) {

  LevelUIHook(self);

  if (getMainConfig().isEnabled.GetValue()) {
    if(!getMainConfig().EnablePlayButton.GetValue()){
      UnityEngine::UI::Button * playMenuButton = self -> dyn__actionButton();
      UnityEngine::GameObject * play = playMenuButton -> get_gameObject();
      play -> SetActive(false);
    }
    else {}
    setActionButton(self -> actionButton);
  } else {}

}

MAKE_HOOK_MATCH(ResultsView, & ResultsViewController::SetDataToUI, void, ResultsViewController * self) {
  ResultsView(self);

  if (getMainConfig().isEnabled.GetValue()) {
    setResultUI(self -> clearedBannerGo);
  }
}

// Called at the early stages of game loading
extern "C"
void setup(ModInfo & info) {
  info.id = MOD_ID;
  info.version = VERSION;
  modInfo = info;

  getConfig().Load();
  getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C"
void load() {
  il2cpp_functions::Init();
  getMainConfig().Init(modInfo);
  // Initialises Quest UI
  QuestUI::Init();
  QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);
  QuestUI::Register::RegisterMainMenuModSettingsViewController(modInfo, DidActivate);
  getLogger().info("Installing hooks...");
  INSTALL_HOOK(getLogger(), ResultsView);
  getLogger().info("Installed all hooks!");
}