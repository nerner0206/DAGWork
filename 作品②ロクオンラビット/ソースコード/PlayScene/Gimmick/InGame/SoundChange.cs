using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundChange : PlayGimmick
{
    [SerializeField, Tooltip("音素材")]
    private AudioClip[] m_audioClips;
    [SerializeField, Tooltip("変更する音")]
    private SoundKind[] m_soundKinds;
    [SerializeField, Tooltip("起動済み")]
    private bool m_playing = false;
    [SerializeField, Tooltip("音を拾うスクリプト")]
    private PlayGimmickSE m_playGimmickSE;

    //  番号
    private int m_num = 0;

    //  音がヒットしたら
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ヒットした音が電気じゃなかったら処理しない || 既に動いている
        if (kind != SoundKind.Electric || m_playing) return;

        m_playing = true;
        //  拾えるようにする
        m_playGimmickSE.OnGimmickSE(m_soundKinds[m_num]);

        //  音の種類を設定
        m_soundKind = m_soundKinds[m_num];
        //  音を渡す
        m_audioSource.clip = m_audioClips[m_num];
        //  再生
        m_audioSource.Play();
    }

    public override void Init()
    {
        m_num = 0;

        m_playGimmickSE.Init();
        m_playGimmickSE.OffGimmickSE();

        if (!m_playing) return;

        //  拾えるようにする
        m_playGimmickSE.OnGimmickSE(m_soundKinds[m_num]);

        //  音の種類を設定
        m_soundKind = m_soundKinds[m_num];
        //  音を渡す
        m_audioSource.clip = m_audioClips[m_num];
        //  再生
        m_audioSource.Play();
    }

    //  音を変更する
    public void HitSoundChange()
    {
        if (!m_playing) return;

        //  次の音へ
        m_num++;
        if(m_num >= m_audioClips.Length) m_num = 0; 

        //  音の種類を設定
        m_soundKind = m_soundKinds[m_num];
        //  拾えるようにする
        m_playGimmickSE.OnGimmickSE(m_soundKind);
        //  音を渡す
        m_audioSource.clip = m_audioClips[m_num];
        //  再生
        m_audioSource.Play();
    }
}
