using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class Switch : EventGimmick
{
    [SerializeField, Tooltip("ロック状態")]
    private bool m_isLock = false;
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;
    [SerializeField, Tooltip("音を拾うスクリプト")]
    private EventGimmickSE m_gimmickSE;

    [SerializeField, Tooltip("起動させるオブジェクト")]
    private PlayGimmick m_playGimmick;

    //  起動状態
    private bool IsPlay = false;

    public override void Init()
    {
        // 音を拾えないようにする
        m_gimmickSE.Init();
        m_gimmickSE.OffGimmickSE();

        //  ロックされてるなら処理しない
        if (m_isLock) return;
        //  音を拾えるようにする
        m_gimmickSE.OnGimmickSE(m_soundKind);
    }

    public override void GimmickReset()
    {
        IsPlay = false;

        //  アニメーター
        m_animator.SetBool("Switch", IsPlay);
        m_playGimmick.SwichOff();
    }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  音の種類を取得
        m_hitSoundKind = kind;

        switch (m_hitSoundKind)
        {
            //  スイッチ音
            case SoundKind.Swich:
                //  動かす
                Event();
                break;
            //  処理しない
            default:
                return;
        }
    }

    public void AttackSwitch()
    {
        //  ロックされたスイッチなら操作させない
        if (m_isLock) return;
        //  動かす
        Event();
    }

    //  SwitchのON/OFF
    public override void Event()
    {
        //  boolを反転させる
        IsPlay = !IsPlay;
        //  アニメーター
        m_animator.SetBool("Switch", IsPlay);

        if (IsPlay) m_playGimmick.SwichOn();
        else m_playGimmick.SwichOff();
    }
}
