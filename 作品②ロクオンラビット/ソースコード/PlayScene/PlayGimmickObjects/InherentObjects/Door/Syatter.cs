using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting.Antlr3.Runtime;
using UnityEngine;

public class Syatter : EventGimmick
{
    [SerializeField, Tooltip("ロック状態")]
    private bool m_isOpen = false;
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;
    [SerializeField, Tooltip("音")]
    private AudioClip[] m_audioClips; 

    public override void Init()
    {
        //  音素材
        m_audioSource.clip = m_audioClips[0];

        //  鍵が空いている処理
        m_animator.SetBool("Open", m_isOpen);

        //  開錠済みなら開錠する
        if (!m_isOpen) return;

        //  音素材
        m_audioSource.clip = m_audioClips[1];
    }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  処理しない
        return;
    }

    //  プレイヤーが触れたとき
    public override void OnTriggerEnter2D(Collider2D collision)
    {
        //  プレイヤー以外なら処理しない
        if (!collision.gameObject.CompareTag("Player")) return;

        //  鍵が掛かっているならロック音を鳴らして処理しない
        if (!m_isOpen)
        {
            m_audioSource.Play();
            return;
        }
    }

    //  開錠する
    public override void Event() { }

    public override void SwichOn()
    {
        //  既に空いているなら処理しない
        if (m_isOpen) return;
        //  ドアを解放する
        m_isOpen = true;
        //  鍵が空いている処理
        m_animator.SetBool("Open", m_isOpen);
    }

    public override void SwichOff()
    {
        //  既に空いているなら処理しない
        if (!m_isOpen) return;
        //  ドアを解放する
        m_isOpen = false;
        //  鍵が空いている処理
        m_animator.SetBool("Open", m_isOpen);
    }
}
