using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

//  破壊されるオブジェクト
public class PlayWoodObj : PlayGimmick
{   
    //  音がヒット
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ヒットした音を取得
        m_hitSoundKind = kind;

        //  音の種類による処理
        switch (m_hitSoundKind)
        {

            //  破壊音
            case SoundKind.WoodBreak:
                HitBreak(pitch);
                break;

            //  処理しない
            default:
                return;
        }
    }

    public override void SoundNot()
    {
        base.SoundNot();
    }
    //  破壊音で壊す処理
    public virtual void HitBreak(float pitch) { }
}
