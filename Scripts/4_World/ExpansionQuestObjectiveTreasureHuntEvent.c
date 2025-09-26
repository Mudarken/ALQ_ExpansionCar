modded class ExpansionQuestObjectiveTreasureHuntEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 6); // 👈 typ treasure

        return true;
    }
}
