using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayBeam : PlayGimmick
{
    [SerializeField, Tooltip("子オブジェクト")]
    private GameObject m_beamMain;
    [SerializeField, Tooltip("最初から稼働しているか")]
    private bool m_isMove = false;
    [SerializeField, Tooltip("音を拾うスクリプト")]
    private PlayGimmickSE m_playGimmickSE;

    [SerializeField, Header("動かしたいギミックが存在するなら")]
    private PlayGimmick m_playGimmick;

    //  最初の状態
    private bool m_startMove = false;

    public override void Init()
    {
        m_playGimmickSE.Init();
        m_playGimmickSE.OffGimmickSE();

        m_beamMain.SetActive(false);

        m_startMove = m_isMove;

        if (!m_isMove) return;
        //  最初から稼働している
        m_playGimmickSE.OnGimmickSE(m_soundKind);

        m_beamMain.SetActive(true);
        m_audioSource.Play();

        if (m_playGimmick != null)
            m_playGimmick.SwichOn();
    }

    public override void GimmickReset()
    {
        m_isMove = m_startMove;
        if(m_startMove)
        {
            //  最初から稼働している
            m_playGimmickSE.OnGimmickSE(m_soundKind);

            m_beamMain.SetActive(true);
            m_audioSource.Play();

            if (m_playGimmick != null)
                m_playGimmick.SwichOn();
        }
        else
        {
            m_playGimmickSE.OffGimmickSE();
            m_audioSource.Stop();
            m_beamMain.SetActive(false);

            if (m_playGimmick != null)
                m_playGimmick.SwichOff();
        }
    }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ビーム以外の音では処理しない
        if (kind != SoundKind.Beam || m_isMove) return;

        //  最初から稼働している
        m_playGimmickSE.OnGimmickSE(m_soundKind);
        //  表示
        m_beamMain.SetActive(true);
        m_audioSource.Play();

        if (m_playGimmick != null)
            m_playGimmick.SwichOn();

        m_isMove = true;
    }
}
