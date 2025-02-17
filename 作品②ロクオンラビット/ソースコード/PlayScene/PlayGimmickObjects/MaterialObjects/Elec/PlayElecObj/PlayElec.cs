using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayElec : PlayElecObj
{
    [SerializeField, Tooltip("電線")]
    private ElecLine[] m_lines;

    [SerializeField, Tooltip("画像")]
    private SpriteRenderer m_spriteRenderer;

    //  逆再生
    private bool m_playback;

    //  初期化
    public override void Init()
    {
        //  電線の初期化
        for (int i = 0; i < m_lines.Length; i++)
        {
            m_lines[i].Init();
        }

        //  通常再生
        m_playback = false;
        m_spriteRenderer.color = new Color(1, 1, 1, 1);
    }

    //  音が接触
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  電気以外処理しない
        if (kind != SoundKind.Electric) return;

        m_audioSource.pitch = pitch;

        //  通常状態＋逆再生
        if(!m_playback && pitch < 0f)
        {
            foreach (var line in m_lines) line.SetElec();
            m_playback = true;
            m_spriteRenderer.color = new Color(1, 0, 0, 1);
        }
        //  逆再生状態＋普通再生
        else if(m_playback && pitch > 0f)
        {
            foreach (var line in m_lines) line.SetElec();
            m_playback = false;
            m_spriteRenderer.color = new Color(1, 1, 1, 1);
        }
    }

    //  リセット
    public override void GimmickReset()
    {
        //  電線の初期化
        for (int i = 0; i < m_lines.Length; i++)
        {
            m_lines[i].Init();
        }

        m_playback = false;
        m_spriteRenderer.color = new Color(1, 1, 1, 1);
    }
}
