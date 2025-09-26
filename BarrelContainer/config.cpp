
   class CfgPatches
  {
	class ALQContainer_Base
	{
		units[] = {"ALQSmallContainer","ALQBigContainer","ALQBarrelContainer","ALQContainer_Base"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Characters_Backpacks","DZ_Characters_Pants","DZ_Characters_Tops","DZ_Gear_Containers","DZ_Data","DZ_Characters","DZ_Characters_Backpacks","DZ_Characters_Pants","DZ_Characters_Tops","DZ_Gear_Containers","DZ_Characters_Headgear","DZ_Weapons_Melee","DZ_Characters_Headgear"};
	};
   };
   class cfgWeapons
{
	class RifleCore;
	class Rifle_Base: RifleCore
	{
		inventorySlot[] = {"Shoulder","Melee","Shoulder1","Shoulder2","Shoulder3","Shoulder4","Shoulder5","Shoulder6","Shoulder7","Shoulder8","Shoulder9","Shoulder10","Shoulder11","Shoulder12","Shoulder13","Shoulder14","Shoulder15","Shoulder16","Shoulder17","Shoulder18","Shoulder19","Shoulder20","Shoulder21","Shoulder22","Shoulder23","Shoulder24","Shoulder25","Shoulder26","Shoulder27","Shoulder28","Shoulder29","Shoulder30","Shoulder31","Shoulder32","Shoulder33","Shoulder34","Shoulder35","Shoulder36","Shoulder37","Shoulder38","Shoulder39","Shoulder40","Shoulder41","Shoulder42","Shoulder43","Shoulder44","Shoulder45","Shoulder46"};
	};

};
    class CfgVehicles
{	
	class Container_Base;
    class ALQContainer_Base: Container_Base
	{
		scope = 0;
		destroyOnEmpty = 0;
		varQuantityDestroyOnMin = 0;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1000000000;
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
				class Melee
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

	class ALQBarrelContainer: ALQContainer_Base
	{
		scope = 2;
		displayName = "$STR_ALQBarrelContainer";
		descriptionShort = "";
		model = "ALQ_ExpansionCar\BarrelContainer\BarrelContainer.p3d";
		bounding = "BSphere";
		handheld = "true";
		carveNavmesh = 1;
		canBeDigged = 0;
		weight = 50000;
		itemSize[] = {10,40};
		physLayer = "item_large";
		attachments[] = {"Shoulder24","Shoulder25"};
		rotationFlags = 0;
		class Cargo
		{
			itemsCargoSize[] = {10,40};
			openable = 0;
			allowOwnedCargoManipulation = 0;
		};
	};
	class ALQBigContainer: ALQContainer_Base
	{
		scope = 2;
		displayName = "Big Container";
		descriptionShort = "Big Container";
		model = "ALQ_ExpansionCar\BigContainer\BigContainer.p3d";
		bounding = "BSphere";
		overrideDrawArea = "3.0";
		forceFarBubble = "true";
		handheld = "true";
		carveNavmesh = 1;
		canBeDigged = 0;
		weight = 50000;
		itemSize[] = {10,10};
		physLayer = "item_large";
		attachments[] = {"Shoulder24","Shoulder25"};
		rotationFlags = 0;
		class Cargo
		{
			itemsCargoSize[] = {10,65};
			openable = 0;
			allowOwnedCargoManipulation = 0;
		};
	};
	class ALQSmallContainer: ALQContainer_Base
	{
		scope = 2;
		displayName = "Small Container";
		descriptionShort = "Small Container";
		model = "ALQ_ExpansionCar\SmallContainer\SmallContainer.p3d";
		bounding = "BSphere";
		overrideDrawArea = "3.0";
		forceFarBubble = "true";
		handheld = "true";
		carveNavmesh = 1;
		canBeDigged = 0;
		weight = 50000;
		itemSize[] = {10,10};
		physLayer = "item_large";
		attachments[] = {"Shoulder24","Shoulder25"};
		rotationFlags = 0;
		class Cargo
		{
			itemsCargoSize[] = {10,50};
			openable = 0;
			allowOwnedCargoManipulation = 0;
		};
	};
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyShoulder24: ProxyAttachment
	{
		scope = 2;
		inventorySlot = "Shoulder24";
		model = "ALQ_ExpansionCar\Proxy\Shoulder24.p3d";
	};
	class ProxyShoulder25: ProxyAttachment
	{
		scope = 2;
		inventorySlot = "Shoulder25";
		model = "ALQ_ExpansionCar\Proxy\Shoulder25.p3d";
	};
};
class CfgSlots
{   
    class Slot_Shoulder{};
    class Slot_Shoulder24: Slot_Shoulder
	{
		name = "Shoulder24";
		displayName = "Rifles";
	};
	class Slot_Shoulder25: Slot_Shoulder
	{
		name = "Shoulder25";
		displayName = "Rifles";
	};
};