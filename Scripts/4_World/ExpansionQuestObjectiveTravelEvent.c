modded class ExpansionQuestObjectiveTravelEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 3); // 👈 typ Travel

        return true;
    }
}
