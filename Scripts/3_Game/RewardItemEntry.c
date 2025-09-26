//RewardItemEntry.c
class RewardItemEntry
{
    string ItemName;
    int Chance;
    int Quantity;
    ref array<string> Attachments;

    void RewardItemEntry()
    {
        Attachments = new array<string>;
    }
}
