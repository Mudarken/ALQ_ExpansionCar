modded class ExpansionQuestObjectiveTargetEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 2); // 👈 typ Target

        return true;
    }
}
