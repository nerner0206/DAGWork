using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MetalBox : PlayMetalObj
{
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;

    public override void Init() { }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  溶ける
        if (kind != SoundKind.Melt) return;

        //  溶ける
        m_animator.SetTrigger("Melt");
    }
}
