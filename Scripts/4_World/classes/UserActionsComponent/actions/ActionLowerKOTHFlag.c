class ActionLowerKOTHFlag : ActionContinuousBase
{
    void ActionLowerKOTHFlag()
    {
        m_CallbackClass = ActionManipulateFlagCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_LOWER_FLAG;
        m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
        m_Text = "#lower_flag";
    }

    override void CreateConditionComponents()
    {
        m_ConditionTarget = new CCTCursor;
        m_ConditionItem = new CCINone;
    }

    override typename GetInputType()
    {
        return ContinuousInteractActionInput;
    }

    override bool HasTarget() { return true; }
    override bool HasProgress() { return true; }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Expansion_KOTHflag flag = Expansion_KOTHflag.Cast(target.GetObject());
        if (!flag) return false;

        return flag.FindAttachmentBySlotName("Material_FPole_Flag") && flag.GetAnimationPhase("flag_mast") < 0.99;
    }

    override void OnFinishProgressServer(ActionData action_data)
    {
        Expansion_KOTHflag flag = Expansion_KOTHflag.Cast(action_data.m_Target.GetObject());
        if (flag)
        {
            flag.AnimateFlagEx(flag.GetAnimationPhase("flag_mast") + 0.1, action_data.m_Player);
        }
    }
}