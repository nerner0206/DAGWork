using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OnFire : PlayGimmick
{
    [SerializeField, Tooltip("炎")]
    private GameObject m_fireObj;
    [SerializeField, Tooltip("炎")]
    private bool m_onFire = false;

    //  開始時の状態
    private bool m_startOn;

    //  初期化
    public override void Init()
    {
        m_startOn = m_onFire;

        //  非表示
        m_fireObj.SetActive(false);
        if (!m_onFire) return;
        //  表示
        m_fireObj.SetActive(true);
    }
    //  リセット
    public override void GimmickReset()
    {
        m_onFire = m_startOn;

        //  非表示
        m_fireObj.SetActive(m_onFire);
    }

    //  音と接触
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        if (m_soundKind != SoundKind.Fire || m_onFire) return;

        m_onFire = true;
        //  炎を表示する
        m_fireObj.SetActive(true);
    }
}
