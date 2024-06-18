using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class GlassWall : PlayGlassObj
{
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;
    [SerializeField, Tooltip("�j��ς�")]
    private bool m_isBreak = false;
    [SerializeField, Tooltip("�����E����͈�")]
    private MomentGimmickSE m_gimmickSE;

    [SerializeField, Tooltip("�K���X")]
    private GameObject m_glass;
    [SerializeField, Tooltip("�K���X�j��")]
    private GameObject m_partR;
    [SerializeField, Tooltip("�K���X�j��")]
    private GameObject m_partL;

    [SerializeField, Tooltip("���̑f��")]
    private AudioClip[] m_audioClips;

    [SerializeField, Tooltip("�K���X�j��")]
    private ParticleSystem m_glassEffect;

    public override void Init()
    {
        //  �������ʉ��ɕς���
        m_audioSource.clip = m_audioClips[0];

        //  ������
        m_gimmickSE.Init();
        //  ����
        m_gimmickSE.OffGimmickSE();

        if (!m_isBreak) return;
        Breaking();
    }

    //  �j�󉹂ŉ󂷏���
    public override void HitBreak(float pitch)
    {
        //  �t�Đ������肷��&&���ɉ��Ă���
        if (pitch < 0 && m_isBreak)
        {
            //  ����
            m_isBreak = false;
            //  �C���A�j���[�V�������Đ�
            //animator.SetBool("Break", isBreak);

            m_glass.SetActive(true);

            m_partR.SetActive(false);
            m_partL.SetActive(false);

            //  ���C���[��؂�ւ���
            int layer = LayerMask.NameToLayer("Ground");
            gameObject.layer = layer;

            //  �������ʉ��ɕς���
            m_audioSource.clip = m_audioClips[0];
            //  �����E���Ȃ�����
            m_gimmickSE.OffGimmickSE();

            //  �����I��
            return;
        }
        else if(pitch > 0 && !m_isBreak)
        {
            //  �ʏ�Đ�
            Breaking();
        }
    }

    //  �j��
    private void Breaking()
    {
        //  ��
        m_isBreak = true;
        //  �j��A�j���[�V�������Đ�
        //animator.SetBool("Break", isBreak);

        m_glass.SetActive(false);

        m_partR.SetActive(true);
        m_partL.SetActive(true);

        //  ���C���[��؂�ւ���
        int layer = LayerMask.NameToLayer("Breaking"); ;
        gameObject.layer = layer;

        //  ����j�󉹂ɕς���
        m_audioSource.clip = m_audioClips[1];

        m_glassEffect.Play();

        //  �炷
        m_audioSource.Play();

        //  �j�󉹂̔���
        m_gimmickSE.OnGimmickSE(m_soundKind, 0.1f);
    }
}
