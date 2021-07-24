#pragma once
#include "framework.h"

namespace Globals
{
	inline UObject* Controller;
	inline UObject* GameState;
	inline UObject* GameMode;
	inline UObject* CheatManager;
	inline UObject* Pawn;
}

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
