using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

[RequireComponent(typeof(Animator))]
//  �j�󂳂��I�u�W�F�N�g
public class PlayGrassObj : PlayGimmick
{
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;

    [SerializeField, Tooltip("�΂̕��G�t�F�N�g")]
    private ParticleSystem m_fireEffect;

    //  �����q�b�g
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        m_hitSoundKind = kind;

        //  �����󂯎��
        m_audioSource.clip = audioClip;
        //  ���̍Đ�����
        m_audioSource.pitch = pitch;

        //  ���̎�ނɂ�鏈��
        switch (m_hitSoundKind)
        {
            case SoundKind.Fire:
                HitFire();
                //  ����炷
                m_audioSource.Play();
                break;

            default:
                //  �������Ȃ�
                return;
        }
    }
    public override void SoundNot()
    {
        base.SoundNot();
    }
    //  ���Z�b�g
    public override void GimmickReset()
    {
        base.GimmickReset();
    }
    //  �j�󏈗�
    public virtual void HitFire()
    {
        //  �A�j���[�^�̍Đ�
        m_animator.SetBool("PlayGrass", true);

        m_fireEffect.Play(); 
    }

    void FireFinish()
    {
        m_audioSource.Stop();
    }
}
