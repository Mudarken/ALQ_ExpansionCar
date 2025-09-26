class Expansion_KOTHflag extends BaseBuildingBase
{
    static const string FLAG_ATTACHMENT_SLOT = "Material_FPole_Flag";
    static const string FLAG_ANIMATION_SOURCE = "flag_mast";

    float m_FlagHeight = 1.0;
    protected int m_ObjectiveID;
    protected int m_ObjectiveType;
    KOTH_Particle m_KOTHSmokeParticle;

    void Expansion_KOTHflag()
    {
        RegisterNetSyncVariableFloat("m_FlagHeight", 0.0, 1.0);
    }

    override void EEInit()
    {
        super.EEInit();

        if (GetGame().IsDedicatedServer())
        {
            BuildFlag();
            AttachFlag(FLAG_ATTACHMENT_SLOT);
            AnimateFlagEx(m_FlagHeight, null);
            SpawnSmokeParticle();
        }
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionRaiseKOTHFlag);
        AddAction(ActionLowerKOTHFlag);
    }

    void SetObjectiveData(int id, int type)
    {
        m_ObjectiveID = id;
        m_ObjectiveType = type;
    }

    int GetObjectiveID()
    {
        return m_ObjectiveID;
    }

    int GetObjectiveType()
    {
        return m_ObjectiveType;
    }

    void AnimateFlagEx(float newHeight, PlayerBase player)
    {
        m_FlagHeight = Math.Clamp(newHeight, 0.0, 1.0);
        SetAnimationPhase(FLAG_ANIMATION_SOURCE, m_FlagHeight);
        SetSynchDirty(); // 🔄 Synchronizacja z klientem
    }

    float GetFlagHeight()
    {
        return GetAnimationPhase(FLAG_ANIMATION_SOURCE);
    }

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        SetAnimationPhase(FLAG_ANIMATION_SOURCE, m_FlagHeight);

        if (m_FlagHeight <= 0.0)
        {
            if (m_KOTHSmokeParticle)
            {
                m_KOTHSmokeParticle.SetKOTHParticleState(eKOTHParticleState.NO_SMOKE);
            }
        }
    }

    void BuildFlag()
    {
        KOTH_BuildPartServer("base", AT_BUILD_PART);
        KOTH_BuildPartServer("support", AT_BUILD_PART);
        KOTH_BuildPartServer("pole", AT_BUILD_PART);
    }

    protected void KOTH_BuildPartServer(string part_name, int action_id)
    {
        ConstructionPart part = GetConstruction().GetConstructionPart(part_name);
        if (!part) return;

        if (part.IsBase()) SetBaseState(true);

        RegisterPartForSync(part.GetId());
        RegisterActionForSync(part.GetId(), action_id);
        SynchronizeBaseState();
        SetPartFromSyncData(part);
        UpdateVisuals();

        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ResetActionSyncData, 100, false, this);
    }

    void AttachFlag(string flagType)
    {
        if (!GetInventory().FindAttachmentByName(flagType))
        {
            GetInventory().CreateAttachment(flagType);
        }
    }

    void SpawnSmokeParticle()
    {
        vector smokePos = GetPosition() + "0 11 0";
        m_KOTHSmokeParticle = KOTH_Particle.Cast(GetGame().CreateObject("KOTH_Particle", smokePos, false));
        if (m_KOTHSmokeParticle)
        {
            m_KOTHSmokeParticle.SetParticleSmokeLoop(ParticleList.GRENADE_M18_WHITE_LOOP);
            m_KOTHSmokeParticle.SetKOTHParticleState(eKOTHParticleState.LOOP);
        }
    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        return false;
    }

    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);
        if (m_KOTHSmokeParticle)
        {
            m_KOTHSmokeParticle.SetKOTHParticleState(eKOTHParticleState.NO_SMOKE);
            GetGame().ObjectDelete(m_KOTHSmokeParticle);
        }
    }
	void StopSmoke()
{
    if (m_KOTHSmokeParticle)
    {
        m_KOTHSmokeParticle.SetKOTHParticleState(eKOTHParticleState.NO_SMOKE);
        GetGame().ObjectDelete(m_KOTHSmokeParticle);
        m_KOTHSmokeParticle = null;
        Print("🛑 Dym został zatrzymany i cząsteczka usunięta.");
    }
}
}
