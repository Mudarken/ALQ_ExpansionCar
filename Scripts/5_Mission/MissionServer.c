//MissionServer.c
modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        Print("🚀 MissionServer.OnInit wywołany");

        RewardConfigInit.InitDefaultConfigs();
        RewardConfig.LoadRewards(); // załaduj nagrody
        RewardCleaner.ClearAllRewards(RewardConfig.Rewards); // usuń stare
    }
}


