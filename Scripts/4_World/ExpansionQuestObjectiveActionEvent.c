modded class ExpansionQuestObjectiveActionEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 10); // 👈 typ action

        return true;
    }
}



