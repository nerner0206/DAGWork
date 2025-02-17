using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayFire : PlayFireObj
{
    //  更新処理
    private void Update()
    {
        //  何の音も触れていない
        if (m_hitSoundKind == SoundKind.Over) return;

        //  音がヒットしたときの処理
        switch(m_hitSoundKind)
        {
            case SoundKind.Water:
                HitWater();
                break;
            default:
                break;
        }
    }
    //  水が接触
    public override void HitWater()
    {
        base.HitWater();
    }
}
