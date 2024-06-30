using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MetalBox : PlayMetalObj
{
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;

    public override void Init() { }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  �n����
        if (kind != SoundKind.Melt) return;

        //  �n����
        m_animator.SetTrigger("Melt");
    }
}
