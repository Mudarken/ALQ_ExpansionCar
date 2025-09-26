// RewardConfigInit.c
class RewardConfigInit
{
    static void InitDefaultConfigs()
    {
        static const string FOLDER = "$profile:ALQ_Expansion";

        if (!FileExist(FOLDER))
        {
            MakeDirectory(FOLDER);
            Print("📁 Folder ALQ_Expansion został utworzony.");
        }

        InitRewardConfig(FOLDER);
        InitVehicleParts(FOLDER);
    }

    static void InitRewardConfig(string folder)
    {
        string rewardPath = folder + "/RewardConfig.json";

        if (!FileExist(rewardPath))
        {
            array<ref RewardConfigData> defaultRewards = new array<ref RewardConfigData>;

            RewardConfigData data = new RewardConfigData;
            data.ObjectiveID = 1;
            data.ObjectiveType = 8;

            // Grupa dla skrzyni
            RewardGroup group1 = new RewardGroup;
            group1.Weight = 20;
            group1.RewardType = "crate";
            group1.Item = "SeaChest";
            group1.Position = "12194.9 12.4887 9691.2";
            group1.Orientation = "0 0 0";  // Dodaj orientację dla skrzyni
            group1.CrateTimer = 120000;  // Dodaj czas timer dla skrzyni
            group1.MinGuaranteedItems = 2;  // Minimalna ilość przedmiotów
            group1.MaxItems = 5;  // Maksymalna ilość przedmiotów

            RewardItemEntry item1 = new RewardItemEntry;
            item1.ItemName = "Map";
            item1.Chance = 100;
            item1.Quantity = 1;

            RewardItemEntry item2 = new RewardItemEntry;
            item2.ItemName = "Compass";
            item2.Chance = 60;
            item2.Quantity = 1;

            group1.Contents.Insert(item1);
            group1.Contents.Insert(item2);

            // Grupa dla pojazdu
            RewardGroup group2 = new RewardGroup;
            group2.Weight = 80;
            group2.RewardType = "vehicle";
            group2.Item = "Truck_01_Covered";
            group2.Position = "12212.6 11.325 9744.45";
            group2.Orientation = "0 0 0";  // Dodaj orientację dla pojazdu
            group2.Parts = {};
            group2.VehicleTimer = 180000;  // Dodaj czas timer dla pojazdu
            group2.MinGuaranteedItems = 1;  // Minimalna ilość przedmiotów
            group2.MaxItems = 3;  // Maksymalna ilość przedmiotów

            RewardItemEntry weapon1 = new RewardItemEntry;
            weapon1.ItemName = "AKM";
            weapon1.Chance = 100;
            weapon1.Quantity = 1;
            weapon1.Attachments.Insert("Mag_AKM_30Rnd");
            weapon1.Attachments.Insert("KobraOptic");

            group2.Contents.Insert(weapon1);

            data.Groups.Insert(group1);
            data.Groups.Insert(group2);
            defaultRewards.Insert(data);

            JsonFileLoader<array<ref RewardConfigData>>.JsonSaveFile(rewardPath, defaultRewards);
            Print("✅ RewardConfig.json wygenerowany automatycznie");
        }
    }

    static void InitVehicleParts(string folder)
    {
        string partsPath = folder + "/VehicleParts.json";

        if (!FileExist(partsPath))
        {
            map<string, ref array<string>> defaultParts = new map<string, ref array<string>>();

            array<string> truckParts = {
                "Truck_01_Wheel",
                "Truck_01_Wheel",
                "Truck_01_WheelDouble",
                "Truck_01_WheelDouble",
                "Truck_01_WheelDouble",
                "Truck_01_WheelDouble",
                "Truck_01_Door_1_1",
                "Truck_01_Door_2_1",
                "Truck_01_Hood",
                "HeadlightH7",
                "HeadlightH7",
                "TruckBattery"
            };
            defaultParts.Insert("Truck_01_Covered", truckParts);

            array<string> hatchbackParts = {
                "HatchbackWheel",
                "HatchbackWheel",
                "HatchbackWheel",
                "HatchbackWheel",
                "HatchbackDoors_Driver",
                "HatchbackDoors_CoDriver",
                "HatchbackHood",
                "CarRadiator",
                "SparkPlug",
                "CarBattery"
            };
            defaultParts.Insert("OffroadHatchback", hatchbackParts);

            JsonFileLoader<map<string, ref array<string>>>.JsonSaveFile(partsPath, defaultParts);
            Print("✅ VehicleParts.json wygenerowany automatycznie");
        }
    }
}