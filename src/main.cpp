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
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "GlobalNamespace/BombExplosionEffect.hpp"
#include "GlobalNamespace/PracticeViewController.hpp"

#include "include/UI/SpeecilTweaksFlowCoordinator.hpp"
#include "include/UI/PlayPracticeViewController.hpp"
#include "include/UI/ResultsEditorViewController.hpp"
#include "GlobalNamespace/LobbySetupViewController.hpp"

#include "GlobalNamespace/PlayerHeightSettingsController.hpp"
#include "System/Math.hpp"


using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace QuestUI;
using namespace custom_types;
using namespace QuestUI::BeatSaberUI;
using namespace TMPro;

DEFINE_CONFIG(MainConfig);

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Returns a logger, useful for printing debug messages
Logger & getLogger() {
  static Logger * logger = new Logger(modInfo);
  return *logger;
}

bool inMulti;
MAKE_HOOK_MATCH(multiCheck, &LobbySetupViewController::DidActivate, void, LobbySetupViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    multiCheck(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    inMulti = true;
    getLogger().info("User connected to multiplayer, not allowing user to alter the active state of the play button");
}

// allows for the results banner and text to be changed
static void setGoodResultUI(UnityEngine::GameObject * clearedBannerGo) {

  clearedBannerGo -> GetComponentsInChildren < TextMeshProUGUI * > ()[0] -> set_text(il2cpp_utils::newcsstr(getMainConfig().rText.GetValue()));
  clearedBannerGo -> GetComponentsInChildren < HMUI::ImageView * > ()[0] -> set_color(getMainConfig().rBackColour.GetValue());

}
static void setBadResultUI(UnityEngine::GameObject * failedBannerGo) {

  failedBannerGo -> GetComponentsInChildren < TextMeshProUGUI * > ()[0] -> set_text(il2cpp_utils::newcsstr(getMainConfig().rfText.GetValue()));
  failedBannerGo -> GetComponentsInChildren < HMUI::ImageView * > ()[0] -> set_color(getMainConfig().rfBackColour.GetValue());

}
// allows for the play button text to be changed
static void setActionButton(UnityEngine::UI::Button * actionButton) {

  actionButton->get_transform()->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->SetText(il2cpp_utils::newcsstr(getMainConfig().aText.GetValue()));

}
static void setPracticeButton(UnityEngine::UI::Button * practiceButton) {

  practiceButton->get_transform()->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->SetText(il2cpp_utils::newcsstr(getMainConfig().pText.GetValue()));

}

static void setPracticePlayButton(UnityEngine::UI::Button * practicePlayButton) {

  practicePlayButton->get_transform()->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->SetText(il2cpp_utils::newcsstr(getMainConfig().aText.GetValue()));

}

MAKE_HOOK_MATCH(MainMenuUIHook, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    inMulti = false;
    getLogger().info("User left Multiplayer, taking control over the play buttons active status.");

    MainMenuUIHook(self, firstActivation, addedToHierarchy, screenSystemEnabling); 

    UnityEngine::UI::Button *soloMenuButton = self->soloButton;
    UnityEngine::GameObject *gameObject = soloMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *soloMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    //
    UnityEngine::UI::Button *onlineMenuButton = self->multiplayerButton;
    UnityEngine::GameObject *gameObject1 = onlineMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *onlineMenuText = gameObject1->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    //
    UnityEngine::UI::Button *campaignMenuButton = self->campaignButton;
    UnityEngine::GameObject *gameObject2 = campaignMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *campaignMenuText = gameObject2->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    //
    UnityEngine::UI::Button *partyMenuButton = self->partyButton;
    UnityEngine::GameObject *gameObject3 = partyMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *partyMenuText = gameObject3->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    //

    soloMenuText->set_color(getMainConfig().MenuButtonColour.GetValue());
    onlineMenuText->set_color(getMainConfig().MenuButtonColour.GetValue());
    campaignMenuText->set_color(getMainConfig().MenuButtonColour.GetValue());
    partyMenuText->set_color(getMainConfig().MenuButtonColour.GetValue());
}



// grabs the play button and if the mod is enabled, it then checks if the user wants the play button to exist, then changes the text of the play button to what the user wants
MAKE_HOOK_MATCH(LevelUIHook, & GlobalNamespace::StandardLevelDetailView::RefreshContent, void, GlobalNamespace::StandardLevelDetailView *
  self) {

  LevelUIHook(self);
  UnityEngine::UI::Button * playMenuButton = self -> actionButton;
  UnityEngine::GameObject * play = playMenuButton -> get_gameObject();
  UnityEngine::UI::Button * practiceMenuButton = self -> practiceButton;
  UnityEngine::GameObject * practice = practiceMenuButton -> get_gameObject();
  if(inMulti){

  }
  else if(!getMainConfig().EnablePlayButton.GetValue()){
      play -> SetActive(false);
      getLogger().info("Disabled the play button");
  }
  else{
    play -> SetActive(true);
    setActionButton(self -> actionButton);
    getLogger().info("Kept the play button enabled");
    getLogger().info("Set Play button text!");
  }
  if(inMulti){

  }
  else if(!getMainConfig().EnablePracticeButton.GetValue()){
      practice -> SetActive(false);
      getLogger().info("Disabled the practice button");
  }
  else{
    practice -> SetActive(true);
    setPracticeButton(self -> practiceButton);
    getLogger().info("Kept the practice button on");
    

    
}}

MAKE_HOOK_MATCH(PracLevelUIHook, & GlobalNamespace::PracticeViewController::RefreshUI, void, GlobalNamespace::PracticeViewController *
  self) {

  PracLevelUIHook(self);
  setPracticePlayButton(self->playButton);
  }

MAKE_HOOK_MATCH(ResultsView, & ResultsViewController::SetDataToUI, void, ResultsViewController * self) {
  ResultsView(self);

  setGoodResultUI(self -> clearedBannerGo);
  setBadResultUI(self -> failedBannerGo);
  getLogger().info("Set the result screen colour");
  getLogger().info("Set the result screen text");


}

MAKE_HOOK_MATCH(BombHook, &GlobalNamespace::BombExplosionEffect::SpawnExplosion, void, GlobalNamespace::BombExplosionEffect* self, UnityEngine::Vector3 pos) {

    BombHook(self, pos);
  UnityEngine::ParticleSystem* bDebris = self->debrisPS;
  UnityEngine::GameObject * BombDebris = bDebris -> get_gameObject();
  UnityEngine::ParticleSystem* bExplosion = self->explosionPS;
  UnityEngine::GameObject * BombExplosion = bExplosion -> get_gameObject();

  if(getMainConfig().DisableBombDebris.GetValue()){
  BombDebris->SetActive(false);
  BombExplosion->SetActive(false);
  }
  else{}
}
// Called at the early stages of game loading
extern "C"
void setup(ModInfo & info) {
  info.id = MOD_ID;
  info.version = VERSION;
  modInfo = info;

  getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C"
void load() {
  il2cpp_functions::Init();
  getMainConfig().Init(modInfo);
  // Initialises Quest UI
  custom_types::Register::AutoRegister();
  QuestUI::Init();
  QuestUI::Register::RegisterMainMenuModSettingsFlowCoordinator<SpeecilTweaks::UI::SpeecilTweaksFlowCoordinator*>(modInfo);
  //QuestUI::Register::RegisterMainMenuModSettingsFlowCoordinator<CustomMissText::UI::FlowCoordinators::CustomMissTextFlowCoordinator*>(modInfo);
  getLogger().info("Installing hooks...");
  INSTALL_HOOK(getLogger(), ResultsView);
  INSTALL_HOOK(getLogger(), LevelUIHook);
  INSTALL_HOOK(getLogger(), MainMenuUIHook);
  INSTALL_HOOK(getLogger(), multiCheck);
  INSTALL_HOOK(getLogger(), BombHook);
  INSTALL_HOOK(getLogger(), PracLevelUIHook);
  getLogger().info("Installed all hooks!");
}