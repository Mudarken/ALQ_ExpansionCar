class ActionRaiseKOTHFlag : ActionContinuousBase
{
    void ActionRaiseKOTHFlag()
    {
        m_CallbackClass = ActionManipulateFlagCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RAISE_FLAG;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
        m_Text = "#raise_flag";
    }

    override void CreateConditionComponents()
    {
        m_ConditionTarget = new CCTCursor;
        m_ConditionItem = new CCINone;
    }

    override typename GetInputType() { return ContinuousInteractActionInput; }
    override bool HasTarget() { return true; }
    override bool HasProgress() { return true; }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
{
    Expansion_KOTHflag totem = Expansion_KOTHflag.Cast(target.GetObject());
    if (!totem) return false;

    float state = totem.GetFlagHeight(); // użycie getter'a

    // Poprawka: rzutowanie i sprawdzenie null
    ItemBase flag = ItemBase.Cast(totem.FindAttachmentBySlotName("Material_FPole_Flag"));
    bool hasFlag = flag != null;

    string flagStatus;
    if (hasFlag)
    {
        flagStatus = "true";
    }
    else
    {
        flagStatus = "false";
    }

    Print("🔍 ActionCondition: hasFlag=" + flagStatus + " | flagHeight=" + state);

    return hasFlag && state > 0.0;
}


    override void OnFinishProgressServer(ActionData action_data)
    {
        Expansion_KOTHflag totem = Expansion_KOTHflag.Cast(action_data.m_Target.GetObject());
        if (!totem) return;

        float currentHeight = totem.GetFlagHeight();
        float newHeight = Math.Clamp(currentHeight - 0.1, 0.0, 1.0);

        Print("🚩 Raising flag from " + currentHeight + " to " + newHeight);
        totem.AnimateFlagEx(newHeight, action_data.m_Player);

        if (totem.m_KOTHSmokeParticle)
        {
            totem.m_KOTHSmokeParticle.SetKOTHParticleState(eKOTHParticleState.NO_SMOKE);
        }

        int objectiveID = totem.GetObjectiveID();
        int objectiveType = totem.GetObjectiveType();

        Print("🎁 Attempting to spawn reward: ID=" + objectiveID + " TYPE=" + objectiveType);
        RewardConfig.SpawnRewardForObjective(objectiveID, objectiveType, totem);
    }
}
