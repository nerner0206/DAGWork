using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundIcon : Sound
{
    //  AudioSources
    private AudioSource m_audioSource;

    //  Rigidbody2D
    private Rigidbody2D m_rb2D;
    //  player‚ÌˆÊ’u
    private Transform m_player;
    //  Ä¶ó‹µ
    private bool m_playBack;
    public bool GetPlayBack() { return m_playBack; }

    //  ‰Šú‰»
    public void Init(Transform p, bool playBack, SoundKind kind, AudioClip clip)
    {
        //  •¨—‹““®
        m_rb2D = gameObject.GetComponent<Rigidbody2D>();
        //  audioSource‚ğæ“¾
        m_audioSource = gameObject.GetComponent<AudioSource>();
        //  player
        m_player = p;

        //  ‰¹‚Ìí—Ş
        m_soundKind = kind;
        //  ‰¹‚Ì‘fŞ
        m_audioSource.clip = clip;
        //  ‰¹‚ğ–Â‚ç‚·
        m_audioSource.Play();

        //  Ä¶•û–@
        this.m_playBack = playBack;
        //  •’ÊÄ¶
        if (this.m_playBack) m_audioSource.pitch = 1;
        //  ‹tÄ¶
        else m_audioSource.pitch = -1;
    }

    private void FixedUpdate()
    {
        //  ˆÊ’u’²®
        gameObject.transform.position = m_player.position;
    }
}
