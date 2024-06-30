using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ElecLine : MonoBehaviour
{
    [SerializeField, Tooltip("���ɂ��Ă��邩")]
    private bool m_startElec = false;
    [SerializeField, Tooltip("�d�C")]
    private GameObject m_Elec;
    [SerializeField, Tooltip("�~�̓����蔻��")]
    private CircleCollider2D m_circleCollider2D;
    [SerializeField, Tooltip("��")]
    private AudioSource m_audioSource;

    //  �ʓd�̐^�U�l
    private bool m_isElec;

    //  ������
    public void Init()
    {
        //  �ŏ��̏��
        m_isElec = m_startElec;

        //  �d�C��ON�EOFF
        m_Elec.SetActive(m_isElec);
        m_circleCollider2D.enabled = m_isElec;
        AudioPlay();
    }

    //  ��Ԃ𔽓]������
    public void SetElec()
    {
        //  �ϊ�
        m_isElec = !m_isElec;

        //  �d�C��ON�EOFF
        m_Elec.SetActive(m_isElec);
        m_circleCollider2D.enabled = m_isElec;
        AudioPlay();
    }

    //  �Đ�or��~
    private void AudioPlay()
    {
        if (m_isElec) m_audioSource.Play();
        else m_audioSource.Stop();
    }
    
}
