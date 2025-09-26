modded class ExpansionQuestObjectiveAICampEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 8); // 👈 typ obozu

        return true;
    }
}



