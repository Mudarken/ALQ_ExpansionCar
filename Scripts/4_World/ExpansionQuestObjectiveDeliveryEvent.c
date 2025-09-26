modded class ExpansionQuestObjectiveDeliveryEvent
{
    override bool OnComplete()
    {
        if (!super.OnComplete())
            return false;

        int objectiveID = m_ObjectiveConfig.GetID();
        RewardConfig.SpawnRewardForObjective(objectiveID, 5); // 👈 typ Delivery

        return true;
    }
}
