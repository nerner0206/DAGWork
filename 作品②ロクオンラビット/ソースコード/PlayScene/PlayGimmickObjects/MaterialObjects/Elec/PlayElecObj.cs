using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class PlayElecObj : PlayGimmick
{
    [SerializeField, Tooltip("�ʓd���Ă��邩")]
    protected bool m_hitElec;

    //  ������
    public override void Init() { }

    //  �����q�b�g����
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  �q�b�g���������󂯎��
        m_hitSoundKind = kind;
        //  �Đ����x��ς���
        m_audioSource.pitch = pitch;

        //  ����
        switch (m_hitSoundKind)
        {
            case SoundKind.Electric:
                //  ���̑f��
                m_audioSource.clip = audioClip;
                HitElec();
                break;
            //  �������Ȃ�
            default:
                return;
        }
    }

    //  �������ꂽ
    public override void SoundNot()
    {
        base.SoundNot();
    }
    //  ���Z�b�g
    public override void GimmickReset() { }

    //  �d�C�̐ڐG
    public virtual void HitElec()
    {
        //  �ʓd��on/off
        m_hitElec = !m_hitElec;
    }
}
