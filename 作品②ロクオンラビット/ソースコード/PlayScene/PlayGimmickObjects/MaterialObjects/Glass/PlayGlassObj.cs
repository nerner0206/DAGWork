using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayGlassObj : PlayGimmick
{
    //  ‰¹‚ªƒqƒbƒg
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        if (kind != SoundKind.GlassBreak) return;

        HitBreak(pitch);
    }

    public override void SoundNot()
    {
        base.SoundNot();
    }
    //  ”j‰ó‰¹‚Å‰ó‚·ˆ—
    public virtual void HitBreak(float pitch) { }
}
