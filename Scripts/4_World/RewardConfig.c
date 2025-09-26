// RewardConfig.c
class RewardConfig
{
    static ref array<ref RewardConfigData> Rewards;

    static void LoadRewards()
    {
        if (!Rewards)
            Rewards = new array<ref RewardConfigData>();
        JsonFileLoader<ref array<ref RewardConfigData>>.JsonLoadFile("$profile:ALQ_Expansion/RewardConfig.json", Rewards);
    }

    static array<ref RewardItemEntry> GetItemsByChance(array<ref RewardItemEntry> entries, int minGuaranteed, int maxItems)
    {
        array<ref RewardItemEntry> selected = new array<ref RewardItemEntry>;

        foreach (RewardItemEntry item : entries)
        {
            for (int i = 0; i < item.Quantity; i++)
            {
                if (Math.RandomInt(0, 100) < item.Chance)
                    selected.Insert(item);
            }
        }

        if (selected.Count() < minGuaranteed)
        {
            array<ref RewardItemEntry> remaining = new array<ref RewardItemEntry>;
            foreach (RewardItemEntry entry : entries)
            {
                bool found = false;
                for (int j = 0; j < selected.Count(); j++)
                {
                    if (selected[j] == entry)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    remaining.Insert(entry);
            }

            while (selected.Count() < minGuaranteed && remaining.Count() > 0)
            {
                int idx1 = Math.RandomInt(0, remaining.Count());  // Zmieniona nazwa zmiennej
                selected.Insert(remaining[idx1]);
                remaining.Remove(idx1);
            }
        }

        if (selected.Count() > maxItems)
        {
            while (selected.Count() > maxItems)
            {
                int idx2 = Math.RandomInt(0, selected.Count());  // Zmieniona nazwa zmiennej
                selected.Remove(idx2);
            }
        }

        return selected;
    }

    static void SpawnVehicleWithParts(RewardGroup group)
    {
		    // 1. DODANE: Ładowanie części pojazdów z bazy danych (jedyna nowa linia)
    VehiclePartsDatabase.Load();

    // 2. Jeśli grupa nie ma zdefiniowanych części, wczytaj domyślne
    if (group.Parts.Count() == 0)
    {
        array<string> autoParts = VehiclePartsDatabase.GetPartsForVehicle(group.Item);
        if (autoParts.Count() > 0)
        {
            group.Parts = autoParts;
            Print("🔧 Części dla pojazdu " + group.Item + " pobrane z VehicleParts.json");
        }
        else
        {
            Print("⚠️ Brak zdefiniowanych części dla pojazdu: " + group.Item);
        }
    }
        // Utwórz pojazd na podstawie pozycji
        vector position = group.Position.ToVector();
        CarScript vehicle = CarScript.Cast(GetGame().CreateObject(group.Item, position));
        
        // Sprawdź, czy pojazd został pomyślnie utworzony
        if (!vehicle)
        {
            Print("❌ Nie udało się stworzyć pojazdu: " + group.Item);
            return;
        }

        // Ustaw orientację pojazdu
        vector orientation = group.Orientation.ToVector();
        vehicle.SetOrientation(orientation);

        // Dodaj części pojazdu
        foreach (string part : group.Parts)
        {
            vehicle.GetInventory().CreateInInventory(part);
        }

        // Wybierz przedmioty z lootem
        array<ref RewardItemEntry> chosenItems = GetItemsByChance(group.Contents, group.MinGuaranteedItems, group.MaxItems);
        foreach (RewardItemEntry entry : chosenItems)
        {
            EntityAI entity = EntityAI.Cast(vehicle.GetInventory().CreateInInventory(entry.ItemName));
            if (entity)
            {
                foreach (string att : entry.Attachments)
                {
                    entity.GetInventory().CreateAttachment(att);
                }
            }
        }

        // Wypełnij paliwo, olej i chłodziwą
        vehicle.Fill(CarFluid.FUEL, Math.RandomFloatInclusive(0.2, 0.8) * vehicle.GetFluidCapacity(CarFluid.FUEL));
        vehicle.Fill(CarFluid.OIL, Math.RandomFloatInclusive(0.1, 0.6) * vehicle.GetFluidCapacity(CarFluid.OIL));
        vehicle.Fill(CarFluid.COOLANT, Math.RandomFloatInclusive(0.3, 1.0) * vehicle.GetFluidCapacity(CarFluid.COOLANT));

        // Ustaw timer dla pojazdu
        if (group.VehicleTimer > 0)
        {
            vector spawnPos = vehicle.GetPosition();
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DeleteEntity, group.VehicleTimer, false, vehicle, spawnPos);
            Print("⏱️ Timer (" + group.VehicleTimer + " ms) rozpoczęty dla pojazdu: " + vehicle.GetType());
        }

        Print("🚗 Pojazd " + group.Item + " został stworzony z lootem.");
    }

    static void SpawnCrateWithLoot(RewardGroup group)
    {
        // Utwórz skrzynię na podstawie pozycji
        vector position = group.Position.ToVector();
        ItemBase crate = ItemBase.Cast(GetGame().CreateObject(group.Item, position));

        // Sprawdź, czy skrzynia została pomyślnie utworzona
        if (!crate)
        {
            Print("❌ Nie udało się stworzyć skrzyni: " + group.Item);
            return;
        }

        // Ustaw orientację skrzyni
        vector orientation = group.Orientation.ToVector();
        crate.SetOrientation(orientation);

        // Wybierz przedmioty z lootem
        array<ref RewardItemEntry> chosenItems = GetItemsByChance(group.Contents, group.MinGuaranteedItems, group.MaxItems);
        foreach (RewardItemEntry entry : chosenItems)
        {
            EntityAI entity = EntityAI.Cast(crate.GetInventory().CreateInInventory(entry.ItemName));
            if (entity)
            {
                foreach (string att : entry.Attachments)
                {
                    entity.GetInventory().CreateAttachment(att);
                }
            }
        }

        // Ustaw timer dla skrzyni
        if (group.CrateTimer > 0)
        {
            vector spawnPos = crate.GetPosition();
            GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DeleteEntity, group.CrateTimer, false, crate, spawnPos);
            Print("⏱️ Timer (" + group.CrateTimer + " ms) rozpoczęty dla skrzyni: " + crate.GetType());
        }

        Print("📦 Skrzynia " + group.Item + " została stworzona z lootem.");
    }

    static void SpawnRewardForObjective(int objectiveID, int objectiveType, Expansion_KOTHflag flagRef = null)
    {
        LoadRewards();

        foreach (RewardConfigData entry : Rewards)
        {
            if (entry.ObjectiveID != objectiveID || entry.ObjectiveType != objectiveType)
                continue;

            RewardCleaner.ClearAllRewards({entry});

            int totalWeight = 0;
            array<int> weights = new array<int>;
            foreach (RewardGroup group : entry.Groups)
            {
                weights.Insert(group.Weight);
                totalWeight += group.Weight;
            }

            int roll = Math.RandomInt(0, totalWeight);
            int acc = 0;
            RewardGroup chosenGroup;

            for (int i = 0; i < entry.Groups.Count(); i++)
            {
                acc += weights[i];
                if (roll < acc)
                {
                    chosenGroup = entry.Groups[i];
                    break;
                }
            }

            if (!chosenGroup)
                return;

            if (chosenGroup.RewardType == "vehicle")
                SpawnVehicleWithParts(chosenGroup);
            else
                SpawnCrateWithLoot(chosenGroup);

            if (flagRef)
            {
                flagRef.StopSmoke();
                Print("💨 Dym na maszcie został zakończony po spawnie nagrody.");
            }
        }
    }

    static void DeleteEntity(EntityAI entity, vector originalPosition)
    {
        if (!entity)
            return;

        vector currentPos = entity.GetPosition();
        float distance = vector.Distance(currentPos, originalPosition);

        if (distance > 2.0) // jeśli obiekt został przesunięty o więcej niż 2 metry
        {
            Print("🚫 Usunięcie anulowane — obiekt został przesunięty: " + entity.GetType());
            return;
        }

        GetGame().ObjectDelete(entity);
        Print("⏱️ Usunięto nagrodę: " + entity.GetType());
    }
}