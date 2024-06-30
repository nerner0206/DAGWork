using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class ElecFan : PlayElecObj
{
    [SerializeField, Tooltip("アニメーター")]
    private Animator m_animator;

    [SerializeField, Tooltip("風")]
    private GameObject m_wind;

    //  開始時に回っているか
    private bool m_startHit = false;

    //  初期化
    public override void Init()
    {
        //  風の表示
        m_wind.SetActive(m_hitElec);
        //  アニメーターの再生
        m_animator.SetBool("Play", m_hitElec);

        //  開始時の状態
        m_startHit = m_hitElec;
    }

    //  電気と接触
    public override void HitElec()
    {
        base.HitElec();

        //  風の表示
        m_wind.SetActive(m_hitElec);
        //  アニメーターの再生
        m_animator.SetBool("Play", m_hitElec);
    }

    //  リセット
    public override void GimmickReset()
    {
        //  最初の状態にする
        m_hitElec = m_startHit;

        //  風の表示
        m_wind.SetActive(m_hitElec);
        //  アニメーターの再生
        m_animator.SetBool("Play", m_hitElec);
    }
}
