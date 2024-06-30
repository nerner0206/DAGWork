using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayBeltObj : PlayGimmick
{
    //  回転方向
    private enum RotDir
    {
        Clock,
        UnClock
    }

    [SerializeField, Tooltip("子オブジェクトのスクリプト")]
    private BeltConveyor m_beltConveyor;
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;

    [SerializeField, Tooltip("最初から稼働しているか")]
    private bool m_isMove = false;
    [SerializeField, Tooltip("デフォルトの回転方向")]
    private RotDir m_defRotDir = RotDir.Clock;

    [SerializeField, Tooltip("音を拾うスクリプト")]
    private PlayGimmickSE m_playGimmickSE;

    [SerializeField, Tooltip("速度")]
    private float m_moveSpeed = 1.0f;

    //  初期状態
    private bool m_startMove = false;

    public bool GetSetIsMove
    {
        get { return m_isMove; }
        set { m_isMove = value; }
    }

    //  初期化
    public override void Init()
    {
        //  初期化
        m_beltConveyor.Init(m_isMove);
        m_playGimmickSE.Init();

        m_startMove = m_isMove;

        //  最初から稼働中
        if (!m_isMove) return;

        BeltPlay();
    }

    //  リセット
    public override void GimmickReset()
    {
        //  最初から稼働していないなら止める
        if (!m_startMove) BeltStop();
        //  最初から稼働しているなら動かす
        else BeltPlay();
    }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  音の種類を取得
        m_hitSoundKind = kind;

        //  音ごとの処理を書く

        //  音の種類による処理
        switch (m_hitSoundKind)
        {
            //  モーター音
            case SoundKind.Motor:
                //  音の速度を取得
                m_audioSource.pitch = pitch;
                //  処理
                HitMotor();
                break;

            //  処理しない
            default:
                return;
        }
    }

    private void HitMotor()
    {
        //  止まっていたら動かす
        if (!m_isMove) BeltPlay();
        //  デフォルトが反時計回り
        else if(UnClockCheck() && m_defRotDir == RotDir.UnClock)
        {
            //  ベルトコンベアの角度
            float angle = gameObject.transform.localEulerAngles.z * Mathf.Deg2Rad;
            //  スピード音の再生速度
            float picth = m_audioSource.pitch * m_moveSpeed;
            
            //  音の再生速度からアニメーションの方向を設定
            m_animator.SetFloat("Speed", picth);

            //  ベルトコンベアの稼働速度を設定
            m_beltConveyor.SetPushDir(angle, -picth);
        }
        //  デフォルトが時計回り
        else if(ClockCheck() && m_defRotDir == RotDir.Clock)
        {
            //  ベルトコンベアの角度
            float angle = gameObject.transform.localEulerAngles.z * Mathf.Deg2Rad;
            //  スピード音の再生速度
            float picth = m_audioSource.pitch + m_moveSpeed;

            //  音の再生速度からアニメーションの方向を設定
            m_animator.SetFloat("Speed", picth);

            //  ベルトコンベアの稼働速度を設定
            m_beltConveyor.SetPushDir(angle, -picth);
        }
    }

    private bool UnClockCheck()
    {
        if (
            //  デフォルト回転 && 逆再生
            (m_animator.GetFloat("Speed") > 0f && m_audioSource.pitch < 0f) ||
            //  逆回転　&&　普通再生
            (m_animator.GetFloat("Speed") < 0f && m_audioSource.pitch > 0f))
        {
            return true;
        }
        return false;
    }
    private bool ClockCheck()
    {
        if (
            //  デフォルト回転 && 逆再生
            (m_animator.GetFloat("Speed") < 0f && m_audioSource.pitch < 0f) ||
            //  逆回転　&&　普通再生
            (m_animator.GetFloat("Speed") > 0f && m_audioSource.pitch > 0f))
        {
            Debug.Log(true);
            return true;
        }
        Debug.Log(false);
        return false;
    }

    //  ベルトコンベアを稼働させる
    private void BeltPlay()
    {
        //  稼働
        m_isMove = true;
        //  音を拾えるようにする
        m_playGimmickSE.OnGimmickSE(m_soundKind);

        //  ベルトコンベアの角度
        float angle = gameObject.transform.localEulerAngles.z * Mathf.Deg2Rad;
        //  スピード音の再生速度
        float picth = m_audioSource.pitch * m_moveSpeed;

        if (m_defRotDir == RotDir.Clock) picth *= -1.0f;

        //  音の再生速度からアニメーションの方向を設定
        m_animator.SetFloat("Speed", picth);

        //  ベルトコンベアを軌道
        m_beltConveyor.GetSetIsOn = true;
        //  ベルトコンベアの稼働速度を設定
        m_beltConveyor.SetPushDir(angle, -picth);

        //  音を再生再生する
        m_audioSource.Play();
    }
    //  ベルトコンベアを止める
    private void BeltStop()
    {
        //  稼働
        m_isMove = false;
        //  アニメーションの設定
        m_animator.SetFloat("Speed", 0.0f);
        //  停止する
        m_audioSource.Stop();
        //  音を拾えないようにする
        m_playGimmickSE.OffGimmickSE();
        //  スクリプトも停止
        m_beltConveyor.GetSetIsOn = false;
    }

    public override void SwichOn()
    {
        BeltPlay();
    }
    public override void SwichOff()
    {
        BeltStop();
    }
}
