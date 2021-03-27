#include "FlowQuest.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FlowQuest"

void FFlowQuest::StartupModule()
{
}

void FFlowQuest::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFlowQuest, FlowQuest)
DEFINE_LOG_CATEGORY(LogQuest);
