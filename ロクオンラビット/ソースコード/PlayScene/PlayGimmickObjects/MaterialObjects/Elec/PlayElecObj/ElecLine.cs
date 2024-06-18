using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ElecLine : MonoBehaviour
{
    [SerializeField, Tooltip("既についているか")]
    private bool m_startElec = false;
    [SerializeField, Tooltip("電気")]
    private GameObject m_Elec;
    [SerializeField, Tooltip("円の当たり判定")]
    private CircleCollider2D m_circleCollider2D;
    [SerializeField, Tooltip("音")]
    private AudioSource m_audioSource;

    //  通電の真偽値
    private bool m_isElec;

    //  初期化
    public void Init()
    {
        //  最初の状態
        m_isElec = m_startElec;

        //  電気のON・OFF
        m_Elec.SetActive(m_isElec);
        m_circleCollider2D.enabled = m_isElec;
        AudioPlay();
    }

    //  状態を反転させる
    public void SetElec()
    {
        //  変換
        m_isElec = !m_isElec;

        //  電気のON・OFF
        m_Elec.SetActive(m_isElec);
        m_circleCollider2D.enabled = m_isElec;
        AudioPlay();
    }

    //  再生or停止
    private void AudioPlay()
    {
        if (m_isElec) m_audioSource.Play();
        else m_audioSource.Stop();
    }
    
}
