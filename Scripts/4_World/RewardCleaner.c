//RewardCleaner.c
class RewardCleaner
{
   static void ClearArea(vector position, float radius = 1.0)
{
    array<Object> objects = new array<Object>;
    GetGame().GetObjectsAtPosition3D(position, radius, objects, null); // 👈 poprawione wywołanie

    foreach (Object obj : objects)
    {
        if (obj.IsInherited(CarScript) || obj.IsInherited(ItemBase))
        {
            GetGame().ObjectDelete(obj);
            Print("🧹 Usunięto obiekt: " + obj.GetType());
        }
    }
}


    static void ClearAllRewards(array<ref RewardConfigData> rewards)
    {
        foreach (RewardConfigData data : rewards)
        {
            foreach (RewardGroup group : data.Groups)
            {
                ClearArea(group.Position.ToVector(), 2.0);
            }
        }
    }
}


