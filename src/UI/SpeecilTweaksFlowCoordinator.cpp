#include "main.hpp"

#include "UI/SpeecilTweaksFlowCoordinator.hpp"


#include "MainConfig.hpp"

#include "System/Action.hpp"
#include "System/Action_1.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace QuestUI;

DEFINE_TYPE(SpeecilTweaks::UI, SpeecilTweaksFlowCoordinator);

void SpeecilTweaks::UI::SpeecilTweaksFlowCoordinator::Awake() {

        PlayPracticeViewController = QuestUI::BeatSaberUI::CreateViewController<SpeecilTweaks::UI::PlayPracticeViewController*>();


        ResultsEditorViewController = QuestUI::BeatSaberUI::CreateViewController<SpeecilTweaks::UI::ResultsEditorViewController*>();

        MiscSettingsViewController = QuestUI::BeatSaberUI::CreateViewController<SpeecilTweaks::UI::MiscSettingsViewController*>();

}


void SpeecilTweaks::UI::SpeecilTweaksFlowCoordinator::DidActivate(bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    if (firstActivation){
    SetTitle("Speecil Tweaks Settings", HMUI::ViewController::AnimationType::In);
    showBackButton = true;
    ProvideInitialViewControllers(PlayPracticeViewController, ResultsEditorViewController, MiscSettingsViewController, nullptr, nullptr);
}}

void SpeecilTweaks::UI::SpeecilTweaksFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController) {
    getMainConfig().config->Write();
    this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
}
