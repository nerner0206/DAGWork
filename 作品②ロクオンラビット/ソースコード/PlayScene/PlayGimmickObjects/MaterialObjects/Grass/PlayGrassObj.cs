using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

[RequireComponent(typeof(Animator))]
//  破壊されるオブジェクト
public class PlayGrassObj : PlayGimmick
{
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;

    [SerializeField, Tooltip("火の粉エフェクト")]
    private ParticleSystem m_fireEffect;

    //  音がヒット
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        m_hitSoundKind = kind;

        //  音を受け取る
        m_audioSource.clip = audioClip;
        //  音の再生方向
        m_audioSource.pitch = pitch;

        //  音の種類による処理
        switch (m_hitSoundKind)
        {
            case SoundKind.Fire:
                HitFire();
                //  音を鳴らす
                m_audioSource.Play();
                break;

            default:
                //  処理しない
                return;
        }
    }
    public override void SoundNot()
    {
        base.SoundNot();
    }
    //  リセット
    public override void GimmickReset()
    {
        base.GimmickReset();
    }
    //  破壊処理
    public virtual void HitFire()
    {
        //  アニメータの再生
        m_animator.SetBool("PlayGrass", true);

        m_fireEffect.Play(); 
    }

    void FireFinish()
    {
        m_audioSource.Stop();
    }
}
