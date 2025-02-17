using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundIcon : Sound
{
    //  AudioSources
    private AudioSource m_audioSource;

    //  Rigidbody2D
    private Rigidbody2D m_rb2D;
    //  playerの位置
    private Transform m_player;
    //  再生状況
    private bool m_playBack;
    public bool GetPlayBack() { return m_playBack; }

    //  初期化
    public void Init(Transform p, bool playBack, SoundKind kind, AudioClip clip)
    {
        //  物理挙動
        m_rb2D = gameObject.GetComponent<Rigidbody2D>();
        //  audioSourceを取得
        m_audioSource = gameObject.GetComponent<AudioSource>();
        //  player
        m_player = p;

        //  音の種類
        m_soundKind = kind;
        //  音の素材
        m_audioSource.clip = clip;
        //  音を鳴らす
        m_audioSource.Play();

        //  再生方法
        this.m_playBack = playBack;
        //  普通再生
        if (this.m_playBack) m_audioSource.pitch = 1;
        //  逆再生
        else m_audioSource.pitch = -1;
    }

    private void FixedUpdate()
    {
        //  位置調整
        gameObject.transform.position = m_player.position;
    }
}
