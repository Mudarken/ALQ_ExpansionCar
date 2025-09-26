modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);

        actions.Insert(ActionRaiseKOTHFlag);
        actions.Insert(ActionLowerKOTHFlag);
		actions.Insert(ActionTurnOnALQRoadFlare);
    }
}
