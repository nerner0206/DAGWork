using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayFire : PlayFireObj
{
    //  XVˆ—
    private void Update()
    {
        //  ‰½‚Ì‰¹‚àG‚ê‚Ä‚¢‚È‚¢
        if (m_hitSoundKind == SoundKind.Over) return;

        //  ‰¹‚ªƒqƒbƒg‚µ‚½‚Æ‚«‚Ìˆ—
        switch(m_hitSoundKind)
        {
            case SoundKind.Water:
                HitWater();
                break;
            default:
                break;
        }
    }
    //  …‚ªÚG
    public override void HitWater()
    {
        base.HitWater();
    }
}
