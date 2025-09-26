modded class ExpansionQuestObjectiveCraftingEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 11); // 👈 typ Crafting
        return true;
    }
}
