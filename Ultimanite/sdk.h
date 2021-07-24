#pragma once
#include "framework.h"

namespace Globals
{
	inline UObject* Controller;
	inline UObject* GameState;
	inline UObject* GameMode;
	inline UObject* CheatManager;
	inline UObject* Pawn;
	inline UObject* FortInventory;
	inline UObject* Quickbar;
}

namespace Offsets
{
	DWORD ItemInstancesOffset;
	DWORD ItemEntriesOffset;
	DWORD ItemEntryOffset;
	DWORD WorldInventoryOffset;
	DWORD QuickBarOffset;
	DWORD GamePhaseOffset;
	DWORD StrongMyHeroOffset;
	DWORD CharacterPartsOffset;
	DWORD AdditionalDataOffset;
	DWORD PlayerStateOffset;
	DWORD FortItemEntryOffset;
}

enum class EFortQuickBars : uint8_t
{
	Primary,
	Secondary,
	Max_None,
	EFortQuickBars_MAX,
};

namespace Kismet
{
	static auto FStringToFName(FString inString) -> FName
	{
		static auto lib = FindObject(L"KismetStringLibrary /Script/Engine.Default__KismetStringLibrary");
		static auto func = FindObject(L"Function /Script/Engine.KismetStringLibrary.Conv_StringToName");

		struct Params
		{
			FString s;
			FName ret;
		};

		Params params;
		params.s = inString;

		ProcessEvent(lib, func, &params);

		return params.ret;
	}
}

//TODO: Move to a class for multiplayer.
namespace Player
{
	static void Jump(UObject* Pawn)
	{
		static UObject* Jump = FindObject(L"Function /Script/Engine.Character.Jump");

		ProcessEvent(Pawn, Jump, nullptr);
	}


	static void SwitchLevel(UObject* InController, FString URL)
	{
		static UObject* SwitchLevel = FindObject(L"Function /Script/Engine.PlayerController.SwitchLevel");

		ProcessEvent(InController, SwitchLevel, &URL);
	}

	static void ServerReadyToStartMatch(UObject* InController)
	{
		static UObject* ServerReadyToStartMatch = FindObject(
			L"Function /Script/FortniteGame.FortPlayerController.ServerReadyToStartMatch");

		ProcessEvent(InController, ServerReadyToStartMatch, nullptr);
	}

	static void Possess(UObject* InController, UObject* InPawn)
	{
		static UObject* Possess = FindObject(L"Function /Script/Engine.Controller.Possess");

		ProcessEvent(InController, Possess, &InPawn);
	}

	static FGuid GetItemGuid(UObject* FortItem)
	{
		static UObject* GetItemGuid = FindObject(L"Function /Script/FortniteGame.FortItem.GetItemGuid");
		FGuid ReturnValue;

		ProcessEvent(FortItem, GetItemGuid, &ReturnValue);
		return ReturnValue;
	}

	static void ServerAddItemInternal(UObject* Quickbars, FGuid Item, EFortQuickBars Quickbar, int Slot)
	{
		static UObject* ServerAddItemInternal = FindObject(L"Function /Script/FortniteGame.FortQuickBars.ServerAddItemInternal");

		struct
		{
			FGuid Item;
			EFortQuickBars Quickbar;
			int Slot;
		} Params;

		Params.Item = Item;
		Params.Quickbar = Quickbar;
		Params.Slot = Slot;

		ProcessEvent(Quickbars, ServerAddItemInternal, &Params);
	}

	static UObject* CreateTemporaryItemInstanceBP(UObject* ItemDefinition, int Count, int Level)
	{
		static UObject* CreateTemporaryItemInstanceBP = FindObject(L"Function /Script/FortniteGame.FortItemDefinition.CreateTemporaryItemInstanceBP");

		struct
		{
			int Count;
			int Level;
			UObject* ReturnValue;
		} Params;

		Params.Count = Count;
		Params.Level = Level;

		ProcessEvent(ItemDefinition, CreateTemporaryItemInstanceBP, &Params);

		return Params.ReturnValue;
	}

	static void SetOwningControllerForTemporaryItem(UObject* Item, UObject* Controller)
	{
		static UObject* SetOwningControllerForTemporaryItem = FindObject(L"Function /Script/FortniteGame.FortItem.SetOwningControllerForTemporaryItem");

		ProcessEvent(Item, SetOwningControllerForTemporaryItem, &Controller);
	}

	static void SetOwner(UObject* TargetActor, UObject* NewOwner)
	{
		static UObject* SetOwner = FindObject(L"Function /Script/Engine.Actor.SetOwner");

		ProcessEvent(TargetActor, SetOwner, &NewOwner);
	}

	static void ServerChoosePart(UObject* Target, TEnumAsByte<EFortCustomPartType> Type, UObject* ChosenCharacterPart)
	{
		static UObject* ServerChoosePart = FindObject(L"Function /Script/FortniteGame.FortPlayerPawn.ServerChoosePart");

		struct
		{
			TEnumAsByte<EFortCustomPartType> Type;
			UObject* ChosenCharacterPart;
		} Params;

		Params.Type = Type;
		Params.ChosenCharacterPart = ChosenCharacterPart;

		ProcessEvent(Target, ServerChoosePart, &Params);
	}
}

namespace Controller
{
	static auto GetPawn(UObject* Controller)
	{
		static UObject* K2_GetPawn = FindObject(
			L"Function /Script/Engine.Controller.K2_GetPawn");

		struct Params
		{
			UObject* ret;
		};

		Params params;

		ProcessEvent(Controller, K2_GetPawn, &params);

		return params.ret;
	}
}

namespace GameState
{
	static UObject* GetAircraft(UObject* InGameState)
	{
		static UObject* GetAircraft = FindObject(
			L"Function /Script/FortniteGame.FortGameStateAthena.GetAircraft");

		struct Params
		{
			UObject* bus;
			int i;
		};

		Params params;

		params.i = 1;

		ProcessEvent(InGameState, GetAircraft, &params);
		return params.bus;
	}

	static void OnRep_GamePhase(UObject* InGameState, EAthenaGamePhase OldGamePhase)
	{
		static UObject* OnRep_GamePhase = FindObject(
			L"Function /Script/FortniteGame.FortGameStateAthena.OnRep_GamePhase");

		ProcessEvent(InGameState, OnRep_GamePhase, &OldGamePhase);
	}
}

namespace CheatManager
{
	static void Summon(UObject* InCheatManager, FString InClassName)
	{
		static UObject* Summon = FindObject(L"Function /Script/Engine.CheatManager.Summon");

		ProcessEvent(InCheatManager, Summon, &InClassName);
	}
}

namespace GameplayStatics
{
	static TArray<UObject*> GetAllActorsOfClass(std::wstring const& ClassFullName)
	{
		struct Parameters
		{
			UObject* World;
			UObject* Class;
			TArray<UObject*> Return;
		};

		Parameters parameters;
		parameters.World = GetWorld();
		parameters.Class = FindObject(ClassFullName);

		ProcessEvent(FindObject(L"GameplayStatics /Script/Engine.Default__GameplayStatics"),
			FindObject(L"Function /Script/Engine.GameplayStatics.GetAllActorsOfClass"), &parameters);

		return parameters.Return;
	}
}

namespace AActor
{
	static FVector GetLocation(UObject* Target)
	{
		struct
		{
			FVector ret;
		} Params;

		ProcessEvent(Target, FindObject(L"Function /Script/Engine.Actor.K2_GetActorLocation"), &Params);

		return Params.ret;
	}

	static void Destroy(UObject* Target)
	{
		ProcessEvent(Target, FindObject(L"Function /Script/Engine.Actor.K2_DestroyActor"), nullptr);
	}
}
