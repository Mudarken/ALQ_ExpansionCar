class ActionTurnOnALQRoadFlare : ActionSingleUseBase
{
    void ActionTurnOnALQRoadFlare()
    {
        m_Text = "#switch_on";
    }

    override void CreateConditionComponents()  
    {   
        m_ConditionItem     = new CCINonRuined();
        m_ConditionTarget   = new CCTNone();
    }

    override bool HasTarget() { return false; }
    override bool HasProneException() { return true; }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (item.IsInherited(ALQRoadFlare))
        {
            m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_LIGHTFLARE;
            m_CommandUIDProne   = DayZPlayerConstants.CMD_ACTIONFB_LITCHEMLIGHT;

            return item.HasEnergyManager() && item.GetCompEM().CanSwitchOn() && item.GetCompEM().CanWork();
        }
        return false;
    }

    override void OnExecuteServer(ActionData action_data)
    {
        if (action_data.m_MainItem && action_data.m_MainItem.HasEnergyManager())
        {
            if (action_data.m_MainItem.GetCompEM().CanWork())
            {
                action_data.m_MainItem.GetCompEM().SwitchOn();
            }
        }
    }
    
    override void OnStartClient(ActionData action_data)
    {
        if (action_data.m_MainItem && action_data.m_MainItem.IsInherited(ALQRoadFlare))
        {
            ALQRoadFlare flare = ALQRoadFlare.Cast(action_data.m_MainItem);
            flare.SetModelState(RoadflareModelStates.UNCAPPED_UNIGNITED);
        }
    }
    
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);

        if (action_data.m_MainItem && action_data.m_MainItem.IsInherited(ALQRoadFlare))
        {
            ALQRoadFlare flare = ALQRoadFlare.Cast(action_data.m_MainItem);
            flare.SetModelState(RoadflareModelStates.UNCAPPED_UNIGNITED);
        }
    }
}
