using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PlayElecObj : PlayGimmick
{
    [SerializeField, Tooltip("通電しているか")]
    protected bool m_hitElec;

    //  初期化
    public override void Init() { }

    //  音がヒットした
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ヒットした音を受け取る
        m_hitSoundKind = kind;
        //  再生速度を変える
        m_audioSource.pitch = pitch;

        //  処理
        switch (m_hitSoundKind)
        {
            case SoundKind.Electric:
                //  音の素材
                m_audioSource.clip = audioClip;
                HitElec();
                break;
            //  処理しない
            default:
                return;
        }
    }

    //  音が離れた
    public override void SoundNot()
    {
        base.SoundNot();
    }
    //  リセット
    public override void GimmickReset() { }

    //  電気の接触
    public virtual void HitElec()
    {
        //  通電のon/off
        m_hitElec = !m_hitElec;
    }
}
