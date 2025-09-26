//VehicleRewardConfig.c
class VehicleRewardDefinition
{
    string VehicleType;
    ref array<string> Parts;
    ref array<string> Components;

    // Dodane pole do obsługi załączników
    ref map<string, ref array<string>> AttachmentsMap;

    void VehicleRewardDefinition()
    {
        Parts = new array<string>;
        Components = new array<string>;
        AttachmentsMap = new map<string, ref array<string>>;
    }
}

class VehicleRewardConfig
{
    static ref array<ref VehicleRewardDefinition> Definitions;

    static void Load()
    {
        if (!Definitions)
            Definitions = new array<ref VehicleRewardDefinition>;

        JsonFileLoader<array<ref VehicleRewardDefinition>>.JsonLoadFile("$profile:ALQ_Expansion/VehicleRewardConfig.json", Definitions);
    }

    static VehicleRewardDefinition GetDefinition(string vehicleType)
    {
        Load();
        foreach (VehicleRewardDefinition def : Definitions)
        {
            if (def.VehicleType == vehicleType)
                return def;
        }
        return null;
    }
}

