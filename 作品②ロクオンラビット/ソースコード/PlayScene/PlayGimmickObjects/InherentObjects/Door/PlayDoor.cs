using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayDoor : EventGimmick
{
    [SerializeField, Tooltip("���b�N���")]
    private bool m_isLock;
    [SerializeField, Tooltip("�h�A�����蔻��")]
    private BoxCollider2D m_co2D;
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;
    [SerializeField, Tooltip("�����E���X�N���v�g")]
    private EventGimmickSE m_gimmickSE;
    [SerializeField, Tooltip("��")]
    private AudioClip[] m_audioClips;
    [SerializeField, Tooltip("��蒼���A�j���[�V����")]
    private string m_animName = "CloseIdle";

    //  �J���Ă���
    private bool m_isOpen;

    public override void Init()
    {
        //  ������
        m_gimmickSE.Init();
        m_isOpen = false;
        //  ���f��
        m_audioSource.clip = m_audioClips[0];

        //  �J���ς݂Ȃ�J������
        if (m_isLock) return;

        //  �����擾�ł���悤�ɂ���
        m_gimmickSE.OnGimmickSE(m_soundKind);
        //  ���f��
        m_audioSource.clip = m_audioClips[1];
    }

    public override void GimmickReset() { }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ���̎�ނ��擾
        m_hitSoundKind = kind;

        switch (m_hitSoundKind)
        {
            //  ���[�^�[��
            case SoundKind.Door:
                //  ���f��
                m_audioSource.clip = m_audioClips[1];
                m_audioSource.pitch = pitch;
                //  �h�A���������
                m_isLock = false;
                //  �����E����悤�ɂ���
                m_gimmickSE.OnGimmickSE(m_soundKind);

                //  �J�����
                m_isOpen = true;
                //  �����󂢂Ă��鏈��
                m_animator.SetBool("Open", m_isOpen);
                //  �����蔻�������
                m_co2D.enabled = false;
                //  �Đ�����
                m_audioSource.Play();

                break;
            //  �������Ȃ�
            default:
                return;
        }
    }

    //  �v���C���[���G�ꂽ�Ƃ�
    public override void OnTriggerEnter2D(Collider2D collision)
    {
        base.OnTriggerEnter2D(collision);

        //  �v���C���[�ȊO�Ȃ珈�����Ȃ�
        if (!collision.gameObject.CompareTag("Player")) return;

        //  �����|�����Ă���Ȃ烍�b�N����炵�ď������Ȃ�
        if (m_isLock)
        {
            m_audioSource.Play();
            return;
        }

        Event();
    }
    //  �v���C���[�����ꂽ�Ƃ�
    private void OnTriggerExit2D(Collider2D collision)
    {
        //  �v���C���[�ȊO�Ȃ珈�����Ȃ�
        if (!collision.gameObject.CompareTag("Player") || m_isLock) return;

        //  �J�����
        m_isOpen = false;
        //  �����󂢂Ă��鏈��
        m_animator.SetBool("Open", m_isOpen);
        //  �����蔻�������
        m_co2D.enabled = true;
    }

    //  �J������
    public override void Event()
    {
        //  �J�����
        m_isOpen = true;
        //  �����󂢂Ă��鏈��
        m_animator.SetBool("Open", m_isOpen);
        //  �����蔻�������
        m_co2D.enabled = false;
        //  �Đ�����
        m_audioSource.Play();
    }

    public override void SwichOn()
    {
        //  ���ɋ󂢂Ă���Ȃ珈�����Ȃ�
        if(!m_isLock)
        //  �h�A���������
        m_isLock = false;
        //  �����E����悤�ɂ���
        m_gimmickSE.OnGimmickSE(m_soundKind);
    }
}
