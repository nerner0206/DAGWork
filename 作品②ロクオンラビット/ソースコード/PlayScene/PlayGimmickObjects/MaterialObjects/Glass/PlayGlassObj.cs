using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayGlassObj : PlayGimmick
{
    //  �����q�b�g
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        if (kind != SoundKind.GlassBreak) return;

        HitBreak(pitch);
    }

    public override void SoundNot()
    {
        base.SoundNot();
    }
    //  �j�󉹂ŉ󂷏���
    public virtual void HitBreak(float pitch) { }
}
