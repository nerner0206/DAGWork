using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayElec : PlayElecObj
{
    [SerializeField, Tooltip("“dü")]
    private ElecLine[] m_lines;

    [SerializeField, Tooltip("‰æ‘œ")]
    private SpriteRenderer m_spriteRenderer;

    //  ‹tÄ¶
    private bool m_playback;

    //  ‰Šú‰»
    public override void Init()
    {
        //  “dü‚Ì‰Šú‰»
        for (int i = 0; i < m_lines.Length; i++)
        {
            m_lines[i].Init();
        }

        //  ’ÊíÄ¶
        m_playback = false;
        m_spriteRenderer.color = new Color(1, 1, 1, 1);
    }

    //  ‰¹‚ªÚG
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  “d‹CˆÈŠOˆ—‚µ‚È‚¢
        if (kind != SoundKind.Electric) return;

        m_audioSource.pitch = pitch;

        //  ’Êíó‘Ô{‹tÄ¶
        if(!m_playback && pitch < 0f)
        {
            foreach (var line in m_lines) line.SetElec();
            m_playback = true;
            m_spriteRenderer.color = new Color(1, 0, 0, 1);
        }
        //  ‹tÄ¶ó‘Ô{•’ÊÄ¶
        else if(m_playback && pitch > 0f)
        {
            foreach (var line in m_lines) line.SetElec();
            m_playback = false;
            m_spriteRenderer.color = new Color(1, 1, 1, 1);
        }
    }

    //  ƒŠƒZƒbƒg
    public override void GimmickReset()
    {
        //  “dü‚Ì‰Šú‰»
        for (int i = 0; i < m_lines.Length; i++)
        {
            m_lines[i].Init();
        }

        m_playback = false;
        m_spriteRenderer.color = new Color(1, 1, 1, 1);
    }
}
