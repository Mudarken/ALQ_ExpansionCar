// Scripts/5_Mission/RewardSpawner.c
class RewardSpawner
{
    static void SpawnVehicleWithParts(RewardGroup group)
    {
        CarScript vehicle = CarScript.Cast(GetGame().CreateObject(group.Item, group.Position.ToVector()));
        if (!vehicle)
        {
            Print("❌ Nie udało się stworzyć pojazdu: " + group.Item);
            return;
        }

        vehicle.SetAllowDamage(false);
        vehicle.SetOrientation("0 0 0");

        foreach (string part : group.Parts)
        {
            vehicle.GetInventory().CreateInInventory(part);
        }

        // Zaktualizowane wywołanie funkcji GetItemsByChance
        array<ref RewardItemEntry> chosenItems = RewardConfig.GetItemsByChance(group.Contents, group.MinGuaranteedItems, group.MaxItems);
        foreach (RewardItemEntry entry : chosenItems)
        {
            EntityAI entity = EntityAI.Cast(vehicle.GetInventory().CreateInInventory(entry.ItemName));
            if (entity)
            {
                // Dodaj timer do usunięcia po 15 minutach
                GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DeleteEntity, 900000, false, entity);

                foreach (string att : entry.Attachments)
                {
                    entity.GetInventory().CreateAttachment(att);
                }
            }
        }

        vehicle.Fill(CarFluid.FUEL, Math.RandomFloatInclusive(0.2, 0.8) * vehicle.GetFluidCapacity(CarFluid.FUEL));
        vehicle.Fill(CarFluid.OIL, Math.RandomFloatInclusive(0.1, 0.6) * vehicle.GetFluidCapacity(CarFluid.OIL));
        vehicle.Fill(CarFluid.COOLANT, Math.RandomFloatInclusive(0.3, 1.0) * vehicle.GetFluidCapacity(CarFluid.COOLANT));

        Print("🚗 Pojazd " + group.Item + " został stworzony z lootem.");
    }

    static void SpawnCrateWithLoot(RewardGroup group)
    {
        ItemBase crate = ItemBase.Cast(GetGame().CreateObject(group.Item, group.Position.ToVector()));
        if (!crate)
        {
            Print("❌ Nie udało się stworzyć skrzyni: " + group.Item);
            return;
        }

        crate.SetAllowDamage(false);
        crate.SetOrientation("0 0 0");

        // Zaktualizowane wywołanie funkcji GetItemsByChance
        array<ref RewardItemEntry> chosenItems = RewardConfig.GetItemsByChance(group.Contents, group.MinGuaranteedItems, group.MaxItems);
        foreach (RewardItemEntry entry : chosenItems)
        {
            EntityAI entity = EntityAI.Cast(crate.GetInventory().CreateInInventory(entry.ItemName));
            if (entity)
            {
                // Dodaj timer do usunięcia po 15 minutach
                GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DeleteEntity, 900000, false, entity);

                foreach (string att : entry.Attachments)
                {
                    entity.GetInventory().CreateAttachment(att);
                }
            }
        }

        Print("📦 Skrzynia " + group.Item + " została stworzona z lootem.");
    }

    static void DeleteEntity(EntityAI entity)
    {
        if (entity)
        {
            GetGame().ObjectDelete(entity);
            Print("⏱️ Usunięto nagrodę: " + entity.GetType());
        }
    }
}