using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class PlayElevatorObj : PlayGimmick
{
    [SerializeField, Tooltip("��镔��")]
    private Transform m_ground;

    [SerializeField, Tooltip("�㏸�ʒu")]
    private Transform m_top;
    [SerializeField, Tooltip("���~�ʒu")]
    private Transform m_bottom;

    [SerializeField, Tooltip("�ŏ�����ғ����Ă��邩")]
    private bool m_isMove = false;

    [SerializeField, Tooltip("�ŏ�����㏸���邩")]
    private bool m_isUp = true;

    [SerializeField, Tooltip("�ړ����x")]
    private float m_moveSpeed = 1.0f;

    [SerializeField, Tooltip("�����E���X�N���v�g")]
    private PlayGimmickSE m_playGimmickSE;

    //  �ړ������̌v�Z
    private Vector3 m_dir;

    //  �A�j���[�^�[
    private Animator m_animator;
    //  �������
    private bool m_startMove = false;
    //  �f�t�H���g���W
    private Vector3 m_defPos;

    //  ������
    public override void Init()
    {
        m_animator = GetComponent<Animator>();

        m_startMove = m_isMove;

        m_defPos = gameObject.transform.position;

        //  �ړ�����
        if (m_isUp) m_dir = (m_top.position - m_ground.position).normalized;
        else m_dir = (m_bottom.position - m_ground.position).normalized;

        m_playGimmickSE.Init();
        m_playGimmickSE.OffGimmickSE();

        if (m_isMove) ElevatorMove();
    }

    public override void GimmickReset()
    {
        gameObject.transform.position = m_defPos;

        if (m_startMove) ElevatorMove();
        else ElevatorStop();
    }

    //  �q�b�g������
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ���̎�ނ��擾
        m_hitSoundKind = kind;

        switch (m_hitSoundKind) 
        {
            //  ���[�^�[��
            case SoundKind.Motor:
                //  �����擾
                m_audioSource.pitch = pitch;
                //  �q�b�g����
                //  ���ɉғ��ς�
                if (m_isMove) ElevatorStop();
                else ElevatorMove();
                break;
            //  �������Ȃ�
            default:
                return;
        }
    }

    //  �G���x�[�^�[���~�߂�
    private void ElevatorMove()
    {
        //  ������
        m_isMove = true;
        //  �A�j���[�^�[�̍Đ�
        m_animator.SetBool("Move", m_isMove);

        //  ��������悤�ɂ���
        m_playGimmickSE.OnGimmickSE(m_soundKind);

        //  �炷
        m_audioSource.Play();
    }
    //  �G���x�[�^�[���ғ�����
    private void ElevatorStop()
    {
        //  �~�߂�
        m_isMove = false;
        //  �A�j���[�^�[�̍Đ�
        m_animator.SetBool("Move", m_isMove);

        //  �������Ȃ��悤�ɂ���
        m_playGimmickSE.OffGimmickSE();

        //  �����~�߂�
        m_audioSource.Stop();
    }

    public override void SwichOn()
    {
        ElevatorMove();
    }
    public override void SwichOff()
    {
        ElevatorStop();
    }

    //  �X�V����
    private void Update()
    {
        //  �������Ȃ�
        if (!m_isMove) return;

        //  �㏸��
        if (m_isUp)
        {
            
            //  �㏸����
            m_ground.position += m_dir * m_moveSpeed * Time.deltaTime;

            //  �㏸���I������
            if(m_ground.position.y >= m_top.position.y)
            {
                //  ���~����
                m_isUp = false;
                //�ړ�������ς���
                m_dir = (m_bottom.position - m_ground.position).normalized;
                
            }
        }
        //  ���~��
        else
        {
            //  ���~����
            m_ground.position += m_dir * m_moveSpeed * Time.deltaTime;

            //  �㏸���I������
            if (m_ground.position.y <= m_bottom.position.y)
            {
                //  ���~����
                m_isUp = true;
                //�ړ�������ς���
                m_dir = (m_top.position - m_ground.position).normalized;
                
            }
        }
    }
}
