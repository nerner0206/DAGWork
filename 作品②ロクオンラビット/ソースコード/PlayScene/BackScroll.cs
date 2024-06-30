using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using NaughtyAttributes;

public class BackScroll : MonoBehaviour
{
    [SerializeField, Tooltip("�������x")]
    private float m_moveSpeed;

    [SerializeField, Tooltip("���[�v���邩�ǂ���")]
    private bool m_loop;

    [SerializeField, Tooltip("�v���C���[")]
    private GameObject m_player;

    [SerializeField, ShowIf("_loop"), Tooltip("���[�̈ʒu")]
    private float m_leftEdge;
    [SerializeField, ShowIf("_loop"), Tooltip("�E�[�̈ʒu")]
    private float m_rightEdge;

    [SerializeField, HideIf("_loop"), Tooltip("�X�N���[���̍��[")]
    private float m_leftScrollEdge;
    [SerializeField, HideIf("_loop"), Tooltip("�X�N���[���̉E�[")]
    private float m_RightScrollEdge;


    //  �v���C���[�̃X�^�[�g�ʒu
    private Vector3 m_playerStartPosition;

    //  �w�i�̃X�N���[���̃X�^�[�g�ʒu
    private Vector3 m_startScrollPosition;

    private void Start()
    {
        //  �v���C���[�̃X�^�[�g�ʒu��ێ�
        m_playerStartPosition = m_player.transform.position;

        //  �X�N���[���̊J�n�ʒu��ێ�
        m_startScrollPosition = this.transform.localPosition;
    }

    private void Update()
    {
        //  ���������[�v�Ȃ̂��ǂ����œ�����ς���
        if (m_loop)
        {
            LoopScroll();
        }
        else
        {
            Scroll();

        }
    }

    //  �X�N���[��
    private void Scroll()
    {
        //  �v���C���[�̌��݈ʒu���擾
        Vector3 nowPlayerPosition = m_player.transform.position;

        //  �v���C���[�����̏ꏊ���
        if (nowPlayerPosition.x < m_leftScrollEdge || nowPlayerPosition.x > m_RightScrollEdge)
        {
            return;
        }

        //  �X�^�[�g�̈ʒu���牡�����ɂǂꂾ���ړ����Ă��邩���v�Z
        float deltaX = nowPlayerPosition.x - m_playerStartPosition.x;

        //  �ړ������̔��]�i�v���C���[���E�ɓ����Ɣw�i�͍��ɓ����j
        deltaX *= -1f;

        //  �v���C���[�̏ꏊ�ɉ����āA�w�i���ʂ̑��x�ŃX�N���[��
        this.transform.localPosition = new Vector3(m_startScrollPosition.x + deltaX * m_moveSpeed, 
            this.transform.localPosition.y,
            this.transform.localPosition.z);
    }

    //  ���[�v�X�N���[��
    private void LoopScroll()
    {
        //  ��葬�x�ō��Ɉړ�
        this.transform.localPosition += new Vector3(-m_moveSpeed, 0f, 0f);

        if (this.transform.localPosition.x < m_leftEdge)
        {
            this.transform.localPosition = new Vector3(m_rightEdge,
                this.transform.localPosition.y,
                this.transform.localPosition.z);
        }
    }
}
