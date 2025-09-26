//ExpansionQuestObjectiveAIPatrolEvent.c
modded class ExpansionQuestObjectiveAIPatrolEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 7); // 👈 typ patrolu

        return true;
    }
}
