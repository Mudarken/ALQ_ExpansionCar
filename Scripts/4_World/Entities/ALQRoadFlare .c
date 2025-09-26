class ALQRoadFlare : Roadflare
{
    void ALQRoadFlare()
    {
        // Możesz tu nadpisać parametry spalania, cząsteczki, dźwięki itd.
    }

    override void SetActions()
    {
        super.SetActions();
        RemoveAction(ActionTurnOnWhileInHands);
        AddAction(ActionTurnOnALQRoadFlare);
    }
}
