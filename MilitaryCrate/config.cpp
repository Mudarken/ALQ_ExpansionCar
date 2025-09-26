
#define _ARMA_

class CfgPatches
{
	class ALQMilitaryCrate_Base
	{
		units[] = {"ALQMilitaryCrate_Base","ALQMilitaryCrate"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Characters_Backpacks","DZ_Characters_Pants","DZ_Characters_Tops","DZ_Gear_Containers","DZ_Data","DZ_Characters","DZ_Characters_Backpacks","DZ_Characters_Pants","DZ_Characters_Tops","DZ_Gear_Containers","DZ_Characters_Headgear","DZ_Weapons_Melee","DZ_Characters_Headgear"};
	};
};
class CfgVehicles
{
	class Container_Base;
	class ALQMilitaryCrate_Base: Container_Base
	{
		scope = 0;
		displayName = "$STR_Crate";
		descriptionShort = "$STR_Crate";
		canBeDigged = 0;
		hiddenSelections[] = {"camo"};
		model = "ALQ_ExpansionCar\MilitaryCrate\crate.p3d";
		physLayer = "item_large";
		class Cargo
		{
			itemsCargoSize[] = {10,50};
			openable = 0;
			allowOwnedCargoManipulation = 1;
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 0;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage = 0;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 0;
					};
				};
			};
		};
	};
	class ALQMilitaryCrate: ALQMilitaryCrate_Base
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"ALQ_ExpansionCar\MilitaryCrate\Crate\crate_co.paa"};
	};
};
