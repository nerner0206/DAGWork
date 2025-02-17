using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayWind : PlayGimmick
{
    [SerializeField, Tooltip("風")]
    private WindMove m_wind;

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        if (kind != SoundKind.Wind) return;
        //  反転していたら
        if (pitch < 0.0f) m_wind.PlayBack();
        //  正常
        else m_wind.PlayFront();
    }

    public override void GimmickReset()
    {
        m_wind.PlayFront();
    }
}
