using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayWind : PlayGimmick
{
    [SerializeField, Tooltip("•—")]
    private WindMove m_wind;

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        if (kind != SoundKind.Wind) return;
        //  ”½“]‚µ‚Ä‚¢‚½‚ç
        if (pitch < 0.0f) m_wind.PlayBack();
        //  ³í
        else m_wind.PlayFront();
    }

    public override void GimmickReset()
    {
        m_wind.PlayFront();
    }
}
