// RewardGroup.c
class RewardGroup
{
    int Weight;
    string RewardType;
    string Item;
    string Position;
    string Orientation;
    int MinGuaranteedItems;
    int MaxItems;  // Dodane pole
    ref array<ref RewardItemEntry> Contents;
    ref array<string> Parts;
    int VehicleTimer;
    int CrateTimer;

    void RewardGroup()
    {
        Contents = new array<ref RewardItemEntry>;
        Parts = new array<string>;
        VehicleTimer = 0;
        CrateTimer = 0;
        Orientation = "0 0 0";
        MaxItems = 0;  // Domyślna wartość
    }
}



