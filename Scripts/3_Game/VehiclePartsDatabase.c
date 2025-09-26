//VehiclePartsDatabase.c
class VehiclePartsDatabase
{
    static ref map<string, ref array<string>> m_VehicleParts;

    static void Load()
    {
        if (!m_VehicleParts)
            m_VehicleParts = new map<string, ref array<string>>();

        string folder = "$profile:ALQ_Expansion";
        string path = folder + "/VehicleParts.json";

        if (!FileExist(folder))
        {
            MakeDirectory(folder);
            Print("📁 Folder ALQ_Expansion został utworzony.");
        }

        if (!FileExist(path))
        {
            Print("⚠️ VehicleParts.json nie istnieje — generuję domyślny plik.");
            GenerateDefault(path);
        }

        JsonFileLoader<map<string, ref array<string>>>.JsonLoadFile(path, m_VehicleParts);
        Print("✅ VehicleParts.json załadowany");
    }

    static void GenerateDefault(string path)
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

        JsonFileLoader<map<string, ref array<string>>>.JsonSaveFile(path, defaultParts);
        Print("🆕 VehicleParts.json został wygenerowany z domyślnymi wpisami.");
    }

    static array<string> GetPartsForVehicle(string vehicleType)
    {
        if (!m_VehicleParts)
            Load();

        if (m_VehicleParts.Contains(vehicleType))
            return m_VehicleParts.Get(vehicleType);

        return new array<string>;
    }
}
