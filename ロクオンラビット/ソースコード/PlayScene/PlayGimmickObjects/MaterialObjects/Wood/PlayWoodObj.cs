using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

//  �j�󂳂��I�u�W�F�N�g
public class PlayWoodObj : PlayGimmick
{   
    //  �����q�b�g
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  �q�b�g���������擾
        m_hitSoundKind = kind;

        //  ���̎�ނɂ�鏈��
        switch (m_hitSoundKind)
        {

            //  �j��
            case SoundKind.WoodBreak:
                HitBreak(pitch);
                break;

            //  �������Ȃ�
            default:
                return;
        }
    }

    public override void SoundNot()
    {
        base.SoundNot();
    }
    //  �j�󉹂ŉ󂷏���
    public virtual void HitBreak(float pitch) { }
}
