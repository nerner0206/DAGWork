using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayBeam : PlayGimmick
{
    [SerializeField, Tooltip("�q�I�u�W�F�N�g")]
    private GameObject m_beamMain;
    [SerializeField, Tooltip("�ŏ�����ғ����Ă��邩")]
    private bool m_isMove = false;
    [SerializeField, Tooltip("�����E���X�N���v�g")]
    private PlayGimmickSE m_playGimmickSE;

    [SerializeField, Header("�����������M�~�b�N�����݂���Ȃ�")]
    private PlayGimmick m_playGimmick;

    //  �ŏ��̏��
    private bool m_startMove = false;

    public override void Init()
    {
        m_playGimmickSE.Init();
        m_playGimmickSE.OffGimmickSE();

        m_beamMain.SetActive(false);

        m_startMove = m_isMove;

        if (!m_isMove) return;
        //  �ŏ�����ғ����Ă���
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
            //  �ŏ�����ғ����Ă���
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
        //  �r�[���ȊO�̉��ł͏������Ȃ�
        if (kind != SoundKind.Beam || m_isMove) return;

        //  �ŏ�����ғ����Ă���
        m_playGimmickSE.OnGimmickSE(m_soundKind);
        //  �\��
        m_beamMain.SetActive(true);
        m_audioSource.Play();

        if (m_playGimmick != null)
            m_playGimmick.SwichOn();

        m_isMove = true;
    }
}
