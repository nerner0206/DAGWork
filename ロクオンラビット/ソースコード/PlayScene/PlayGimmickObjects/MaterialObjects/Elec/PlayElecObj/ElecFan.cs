using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class ElecFan : PlayElecObj
{
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;

    [SerializeField, Tooltip("��")]
    private GameObject m_wind;

    //  �J�n���ɉ���Ă��邩
    private bool m_startHit = false;

    //  ������
    public override void Init()
    {
        //  ���̕\��
        m_wind.SetActive(m_hitElec);
        //  �A�j���[�^�[�̍Đ�
        m_animator.SetBool("Play", m_hitElec);

        //  �J�n���̏��
        m_startHit = m_hitElec;
    }

    //  �d�C�ƐڐG
    public override void HitElec()
    {
        base.HitElec();

        //  ���̕\��
        m_wind.SetActive(m_hitElec);
        //  �A�j���[�^�[�̍Đ�
        m_animator.SetBool("Play", m_hitElec);
    }

    //  ���Z�b�g
    public override void GimmickReset()
    {
        //  �ŏ��̏�Ԃɂ���
        m_hitElec = m_startHit;

        //  ���̕\��
        m_wind.SetActive(m_hitElec);
        //  �A�j���[�^�[�̍Đ�
        m_animator.SetBool("Play", m_hitElec);
    }
}
