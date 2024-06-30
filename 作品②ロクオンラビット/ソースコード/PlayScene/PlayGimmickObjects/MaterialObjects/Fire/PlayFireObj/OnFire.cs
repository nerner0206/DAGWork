using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OnFire : PlayGimmick
{
    [SerializeField, Tooltip("��")]
    private GameObject m_fireObj;
    [SerializeField, Tooltip("��")]
    private bool m_onFire = false;

    //  �J�n���̏��
    private bool m_startOn;

    //  ������
    public override void Init()
    {
        m_startOn = m_onFire;

        //  ��\��
        m_fireObj.SetActive(false);
        if (!m_onFire) return;
        //  �\��
        m_fireObj.SetActive(true);
    }
    //  ���Z�b�g
    public override void GimmickReset()
    {
        m_onFire = m_startOn;

        //  ��\��
        m_fireObj.SetActive(m_onFire);
    }

    //  ���ƐڐG
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        if (m_soundKind != SoundKind.Fire || m_onFire) return;

        m_onFire = true;
        //  ����\������
        m_fireObj.SetActive(true);
    }
}
