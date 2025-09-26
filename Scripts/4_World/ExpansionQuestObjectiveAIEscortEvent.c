modded class ExpansionQuestObjectiveAIEscortEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 9); // 👈 typ eskort VIP

        return true;
    }
}