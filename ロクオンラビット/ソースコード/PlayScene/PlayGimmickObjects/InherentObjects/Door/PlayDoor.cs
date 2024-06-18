using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayDoor : EventGimmick
{
    [SerializeField, Tooltip("ロック状態")]
    private bool m_isLock;
    [SerializeField, Tooltip("ドア当たり判定")]
    private BoxCollider2D m_co2D;
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;
    [SerializeField, Tooltip("音を拾うスクリプト")]
    private EventGimmickSE m_gimmickSE;
    [SerializeField, Tooltip("音")]
    private AudioClip[] m_audioClips;
    [SerializeField, Tooltip("やり直しアニメーション")]
    private string m_animName = "CloseIdle";

    //  開いている
    private bool m_isOpen;

    public override void Init()
    {
        //  初期化
        m_gimmickSE.Init();
        m_isOpen = false;
        //  音素材
        m_audioSource.clip = m_audioClips[0];

        //  開錠済みなら開錠する
        if (m_isLock) return;

        //  音を取得できるようにする
        m_gimmickSE.OnGimmickSE(m_soundKind);
        //  音素材
        m_audioSource.clip = m_audioClips[1];
    }

    public override void GimmickReset() { }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  音の種類を取得
        m_hitSoundKind = kind;

        switch (m_hitSoundKind)
        {
            //  モーター音
            case SoundKind.Door:
                //  音素材
                m_audioSource.clip = m_audioClips[1];
                m_audioSource.pitch = pitch;
                //  ドアを解放する
                m_isLock = false;
                //  音を拾えるようにする
                m_gimmickSE.OnGimmickSE(m_soundKind);

                //  開く状態
                m_isOpen = true;
                //  鍵が空いている処理
                m_animator.SetBool("Open", m_isOpen);
                //  当たり判定を消す
                m_co2D.enabled = false;
                //  再生する
                m_audioSource.Play();

                break;
            //  処理しない
            default:
                return;
        }
    }

    //  プレイヤーが触れたとき
    public override void OnTriggerEnter2D(Collider2D collision)
    {
        base.OnTriggerEnter2D(collision);

        //  プレイヤー以外なら処理しない
        if (!collision.gameObject.CompareTag("Player")) return;

        //  鍵が掛かっているならロック音を鳴らして処理しない
        if (m_isLock)
        {
            m_audioSource.Play();
            return;
        }

        Event();
    }
    //  プレイヤーが離れたとき
    private void OnTriggerExit2D(Collider2D collision)
    {
        //  プレイヤー以外なら処理しない
        if (!collision.gameObject.CompareTag("Player") || m_isLock) return;

        //  開く状態
        m_isOpen = false;
        //  鍵が空いている処理
        m_animator.SetBool("Open", m_isOpen);
        //  当たり判定を消す
        m_co2D.enabled = true;
    }

    //  開錠する
    public override void Event()
    {
        //  開く状態
        m_isOpen = true;
        //  鍵が空いている処理
        m_animator.SetBool("Open", m_isOpen);
        //  当たり判定を消す
        m_co2D.enabled = false;
        //  再生する
        m_audioSource.Play();
    }

    public override void SwichOn()
    {
        //  既に空いているなら処理しない
        if(!m_isLock)
        //  ドアを解放する
        m_isLock = false;
        //  音を拾えるようにする
        m_gimmickSE.OnGimmickSE(m_soundKind);
    }
}
