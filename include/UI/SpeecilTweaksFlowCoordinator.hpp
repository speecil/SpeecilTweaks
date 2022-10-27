#pragma once

#include "HMUI/ViewController.hpp"
#include "HMUI/FlowCoordinator.hpp"

#include "UI/PlayPracticeViewController.hpp"
#include "UI/ResultsEditorViewController.hpp"
#include "UI/MiscSettingsViewController.hpp"
#include "UI/CreditsViewController.hpp"

#include "custom-types/shared/macros.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

DECLARE_CLASS_CODEGEN(SpeecilTweaks::UI, SpeecilTweaksFlowCoordinator, HMUI::FlowCoordinator,
                      DECLARE_INSTANCE_FIELD(SpeecilTweaks::UI::ResultsEditorViewController*, ResultsEditorViewController);
                      DECLARE_INSTANCE_FIELD(SpeecilTweaks::UI::PlayPracticeViewController*, PlayPracticeViewController);
                      DECLARE_INSTANCE_FIELD(SpeecilTweaks::UI::MiscSettingsViewController*, MiscSettingsViewController);
                      DECLARE_INSTANCE_FIELD(SpeecilTweaks::UI::CreditsViewController*, CreditsViewController);
                      //fortnite

                      DECLARE_INSTANCE_METHOD(void, Awake);

                      DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::FlowCoordinator::DidActivate>::get(), bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling);
                      DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::FlowCoordinator::BackButtonWasPressed>::get(), HMUI::ViewController* topViewController);
                      )