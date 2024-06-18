using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

//  破壊されるオブジェクト
public class PlayMetalObj : PlayGimmick
{
    //  音がヒット
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        m_hitSoundKind = kind;
    }

    //  溶ける処理
    public virtual void HitMelt() { }
}
