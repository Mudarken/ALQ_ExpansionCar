#define _ARMA_

class CfgPatches
{
    class ALQ_ExpansionCar
    {
        units[] = {"Expansion_KOTHflag"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DayZExpansion_Core",
            "DayZExpansion_Quests",
            "CF_QuestSystem",
            "ExpansionQuestSystem"			// jeśli korzystasz z Expansion Quests
        };
    };
};

class CfgMods
{
    class ALQ_ExpansionCar
    {
        dir = "ALQ_ExpansionCar";
        name = "Antenna listening quest";
        picture = ""; // opcjonalnie: ścieżka do logo moda
        hidePicture = 1;
        hideName = 0;
        action = "";
        type = "mod";
        dependencies[] = {"Mission","Game","World"};
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"ALQ_ExpansionCar/Scripts/3_Game"};
            };
            class missionScriptModule
            {
                value = "";
                files[] = {"ALQ_ExpansionCar/Scripts/5_Mission"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"ALQ_ExpansionCar/Scripts/4_World"};
            };
        };
    };
};
class CfgVehicles
{
	class BaseBuildingBase;
	class Inventory_Base;
	class Container_Base;
	class HouseNoDestruct;
	class Expansion_KOTHflag: BaseBuildingBase
	{
		scope = 2;
		displayName = "KOTH Flag";
		descriptionShort = "";
		model = "\DZ\gear\camping\territory_flag.p3d";
		bounding = "BSphere";
		overrideDrawArea = "3.0";
		forceFarBubble = "true";
		handheld = "false";
		lootCategory = "Crafted";
		carveNavmesh = 1;
		weight = 60000;
		itemSize[] = {6,6};
		physLayer = "item_large";
		createProxyPhysicsOnInit = "true";
		createdProxiesOnInit[] = {"Base","Support","Pole"};
		rotationFlags = 2;
		attachments[] = {"Material_FPole_Flag"};
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
		class GUIInventoryAttachmentsProps
		{
			class Flag
			{
				name = "$STR_CfgVehicles_TerritoryFlag_Att_Category_Flag";
				description = "";
				attachmentSlots[] = {"Material_FPole_Flag"};
				icon = "set:dayz_inventory image:tf_flag";
				selection = "totem";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 0;
			};
			class AnimSourceHidden
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 1;
			};
			class flag_mast
			{
				source = "user";
				initPhase = 1;
				animPeriod = 1;
			};
			class Deployed: AnimSourceHidden{};
			class Base: AnimSourceHidden{};
			class Support: AnimSourceHidden{};
			class Pole: AnimSourceHidden{};
		};
		class Construction
		{
			class totem
			{
				class base
				{
					name = "$STR_CfgVehicles_Construction_Part_Base";
					is_base = 1;
					id = 1;
					platform_support = "support";
					required_parts[] = {};
					conflicted_parts[] = {};
					collision_data[] = {"base_min","base_max"};
					build_action_type = 16;
					dismantle_action_type = 16;
					material_type = 1;
					class Materials
					{
						class Material1
						{
							type = "WoodenLog";
							slot_name = "Material_FPole_WoodenLog";
							quantity = 1;
							lockable = 0;
						};
					};
				};
				class support
				{
					name = "$STR_CfgVehicles_TerritoryFlag_Att_Category_Support";
					id = 2;
					platform_support = "pole";
					required_parts[] = {"base"};
					conflicted_parts[] = {};
					collision_data[] = {"support_min","support_max"};
					build_action_type = 36;
					dismantle_action_type = 36;
					material_type = 2;
					class Materials
					{
						class Material1
						{
							type = "Stone";
							slot_name = "Material_FPole_Stones";
							quantity = 32;
							lockable = 0;
						};
						class Material2
						{
							type = "WoodenLog";
							slot_name = "Material_FPole_WoodenLog2";
							quantity = 6;
							lockable = 0;
						};
					};
				};
				class pole
				{
					name = "$STR_CfgVehicles_TerritoryFlag_Att_Category_Pole";
					id = 3;
					required_parts[] = {"support"};
					conflicted_parts[] = {};
					collision_data[] = {"pole_min","pole_max"};
					build_action_type = 2;
					dismantle_action_type = 64;
					material_type = 2;
					class Materials
					{
						class Material1
						{
							type = "MetalWire";
							slot_name = "Material_FPole_MetalWire";
							quantity = 0;
							lockable = 1;
						};
						class Material2
						{
							type = "Rope";
							slot_name = "Material_FPole_Rope";
							quantity = 0;
							lockable = 1;
						};
						class Material3
						{
							type = "Nail";
							slot_name = "Material_FPole_Nails";
							quantity = 60;
							lockable = 0;
						};
						class Material4
						{
							type = "WoodenLog";
							slot_name = "Material_FPole_MagicStick";
							quantity = 3;
							lockable = 0;
						};
					};
				};
			};
		};
	};
	class KOTH_Particle: HouseNoDestruct
	{
		scope = 2;
	};
	class RoadFlare;
	class ALQRoadFlare: RoadFlare
	{
		scope=2;
		displayName="ALQ Road Flare";
		descriptionShort="$STR_CfgVehicles_Roadflare1";
		model="ALQ_ExpansionCar\ALQRoadFlare\ALQroad_flare.p3d";
		overrideDrawArea="8.0";
		lockType=4;
		weight=50;
		weightPerQuantityUnit=0;
		absorbency=0.5;
		itemSize[]={1,3};
		stackedUnit="w";
		quantityBar=1;
		varQuantityInit=20;
		varQuantityMin=0;
		varQuantityMax=20;
		varQuantityDestroyOnMin=0;
		inventorySlot[]=
		{
			"tripWireAttachment"
		};
		rotationFlags=17;
		hiddenSelections[]=
		{
			"Burning",
			"Burned_out",
			"Pristine",
			"All"
		};
		hiddenSelectionsTextures[]=
		{
			"ALQ_ExpansionCar\ALQRoadFlare\ALQ_road_flare_co.paa"
		};
	};	
};	