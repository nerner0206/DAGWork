using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting.Antlr3.Runtime;
using UnityEngine;

public class Syatter : EventGimmick
{
    [SerializeField, Tooltip("���b�N���")]
    private bool m_isOpen = false;
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;
    [SerializeField, Tooltip("��")]
    private AudioClip[] m_audioClips; 

    public override void Init()
    {
        //  ���f��
        m_audioSource.clip = m_audioClips[0];

        //  �����󂢂Ă��鏈��
        m_animator.SetBool("Open", m_isOpen);

        //  �J���ς݂Ȃ�J������
        if (!m_isOpen) return;

        //  ���f��
        m_audioSource.clip = m_audioClips[1];
    }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  �������Ȃ�
        return;
    }

    //  �v���C���[���G�ꂽ�Ƃ�
    public override void OnTriggerEnter2D(Collider2D collision)
    {
        //  �v���C���[�ȊO�Ȃ珈�����Ȃ�
        if (!collision.gameObject.CompareTag("Player")) return;

        //  �����|�����Ă���Ȃ烍�b�N����炵�ď������Ȃ�
        if (!m_isOpen)
        {
            m_audioSource.Play();
            return;
        }
    }

    //  �J������
    public override void Event() { }

    public override void SwichOn()
    {
        //  ���ɋ󂢂Ă���Ȃ珈�����Ȃ�
        if (m_isOpen) return;
        //  �h�A���������
        m_isOpen = true;
        //  �����󂢂Ă��鏈��
        m_animator.SetBool("Open", m_isOpen);
    }

    public override void SwichOff()
    {
        //  ���ɋ󂢂Ă���Ȃ珈�����Ȃ�
        if (!m_isOpen) return;
        //  �h�A���������
        m_isOpen = false;
        //  �����󂢂Ă��鏈��
        m_animator.SetBool("Open", m_isOpen);
    }
}
