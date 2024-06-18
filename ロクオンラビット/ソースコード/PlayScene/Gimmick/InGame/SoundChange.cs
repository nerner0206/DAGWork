using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundChange : PlayGimmick
{
    [SerializeField, Tooltip("‰¹‘fŞ")]
    private AudioClip[] m_audioClips;
    [SerializeField, Tooltip("•ÏX‚·‚é‰¹")]
    private SoundKind[] m_soundKinds;
    [SerializeField, Tooltip("‹N“®Ï‚İ")]
    private bool m_playing = false;
    [SerializeField, Tooltip("‰¹‚ğE‚¤ƒXƒNƒŠƒvƒg")]
    private PlayGimmickSE m_playGimmickSE;

    //  ”Ô†
    private int m_num = 0;

    //  ‰¹‚ªƒqƒbƒg‚µ‚½‚ç
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ƒqƒbƒg‚µ‚½‰¹‚ª“d‹C‚¶‚á‚È‚©‚Á‚½‚çˆ—‚µ‚È‚¢ || Šù‚É“®‚¢‚Ä‚¢‚é
        if (kind != SoundKind.Electric || m_playing) return;

        m_playing = true;
        //  E‚¦‚é‚æ‚¤‚É‚·‚é
        m_playGimmickSE.OnGimmickSE(m_soundKinds[m_num]);

        //  ‰¹‚Ìí—Ş‚ğİ’è
        m_soundKind = m_soundKinds[m_num];
        //  ‰¹‚ğ“n‚·
        m_audioSource.clip = m_audioClips[m_num];
        //  Ä¶
        m_audioSource.Play();
    }

    public override void Init()
    {
        m_num = 0;

        m_playGimmickSE.Init();
        m_playGimmickSE.OffGimmickSE();

        if (!m_playing) return;

        //  E‚¦‚é‚æ‚¤‚É‚·‚é
        m_playGimmickSE.OnGimmickSE(m_soundKinds[m_num]);

        //  ‰¹‚Ìí—Ş‚ğİ’è
        m_soundKind = m_soundKinds[m_num];
        //  ‰¹‚ğ“n‚·
        m_audioSource.clip = m_audioClips[m_num];
        //  Ä¶
        m_audioSource.Play();
    }

    //  ‰¹‚ğ•ÏX‚·‚é
    public void HitSoundChange()
    {
        if (!m_playing) return;

        //  Ÿ‚Ì‰¹‚Ö
        m_num++;
        if(m_num >= m_audioClips.Length) m_num = 0; 

        //  ‰¹‚Ìí—Ş‚ğİ’è
        m_soundKind = m_soundKinds[m_num];
        //  E‚¦‚é‚æ‚¤‚É‚·‚é
        m_playGimmickSE.OnGimmickSE(m_soundKind);
        //  ‰¹‚ğ“n‚·
        m_audioSource.clip = m_audioClips[m_num];
        //  Ä¶
        m_audioSource.Play();
    }
}
