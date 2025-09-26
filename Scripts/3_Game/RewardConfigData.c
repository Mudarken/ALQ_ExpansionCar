//RewardConfigData.c
class RewardConfigData
{
    int ObjectiveID;
    int ObjectiveType;
    ref array<ref RewardGroup> Groups;

    void RewardConfigData()
    {
        Groups = new array<ref RewardGroup>;
    }
}

