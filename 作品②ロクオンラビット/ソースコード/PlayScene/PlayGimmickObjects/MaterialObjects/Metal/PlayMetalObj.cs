using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

//  �j�󂳂��I�u�W�F�N�g
public class PlayMetalObj : PlayGimmick
{
    //  �����q�b�g
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        m_hitSoundKind = kind;
    }

    //  �n���鏈��
    public virtual void HitMelt() { }
}
