#define _ARMA_

class CfgPatches
{
	class ALQGreenCrate_Base
	{
		units[] = {"ALQGreenCrate_Base","ALQGreenCrate"};
		weapons[] = {};
		requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Characters","DZ_Characters_Backpacks","DZ_Characters_Pants","DZ_Characters_Tops","DZ_Gear_Containers","DZ_Data","DZ_Characters","DZ_Characters_Backpacks","DZ_Characters_Pants","DZ_Characters_Tops","DZ_Gear_Containers","DZ_Characters_Headgear","DZ_Weapons_Melee","DZ_Characters_Headgear"};
	};
};
class CfgVehicles
{
	class WoodenCrate;
	class ALQGreenCrate_Base: WoodenCrate 
	{
		scope = 0;
		displayName = "$STR_ALQGreenCrate";
		descriptionShort = "";
		model = "ALQ_ExpansionCar\GreenCrate\wooden_case.p3d";
		weight = 7000;
		itemSize[] = {10,14};
		class Cargo
		{
			itemsCargoSize[] = {10,10};
			openable = 0;
			allowOwnedCargoManipulation = 1;
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 500;
					healthLevels[] = {{1,{"ALQ_ExpansionCar\GreenCrate\data\wooden_case.rvmat"}},{0.7,{"ALQ_ExpansionCar\GreenCrate\data\wooden_case.rvmat"}},{0.5,{"ALQ_ExpansionCar\GreenCrate\data\wooden_case_damage.rvmat"}},{0.3,{"ALQ_ExpansionCar\GreenCrate\data\wooden_case_damage.rvmat"}},{0,{"ALQ_ExpansionCar\GreenCrate\data\wooden_case_destruct.rvmat"}}};
				};
			};
		};
	};
	class ALQGreenCrate: ALQGreenCrate_Base
	{
		scope = 2;
		class Cargo
		{
			
			itemsCargoSize[] = {10,50};
			openable = 0;
			allowOwnedCargoManipulation = 1;
		};
	};
	
};
