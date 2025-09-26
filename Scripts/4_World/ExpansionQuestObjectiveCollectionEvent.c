modded class ExpansionQuestObjectiveCollectionEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 4); // 👈 typ Collection

        return true;
    }
}
