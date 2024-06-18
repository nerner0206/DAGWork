using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class Switch : EventGimmick
{
    [SerializeField, Tooltip("���b�N���")]
    private bool m_isLock = false;
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;
    [SerializeField, Tooltip("�����E���X�N���v�g")]
    private EventGimmickSE m_gimmickSE;

    [SerializeField, Tooltip("�N��������I�u�W�F�N�g")]
    private PlayGimmick m_playGimmick;

    //  �N�����
    private bool IsPlay = false;

    public override void Init()
    {
        // �����E���Ȃ��悤�ɂ���
        m_gimmickSE.Init();
        m_gimmickSE.OffGimmickSE();

        //  ���b�N����Ă�Ȃ珈�����Ȃ�
        if (m_isLock) return;
        //  �����E����悤�ɂ���
        m_gimmickSE.OnGimmickSE(m_soundKind);
    }

    public override void GimmickReset()
    {
        IsPlay = false;

        //  �A�j���[�^�[
        m_animator.SetBool("Switch", IsPlay);
        m_playGimmick.SwichOff();
    }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ���̎�ނ��擾
        m_hitSoundKind = kind;

        switch (m_hitSoundKind)
        {
            //  �X�C�b�`��
            case SoundKind.Swich:
                //  ������
                Event();
                break;
            //  �������Ȃ�
            default:
                return;
        }
    }

    public void AttackSwitch()
    {
        //  ���b�N���ꂽ�X�C�b�`�Ȃ瑀�삳���Ȃ�
        if (m_isLock) return;
        //  ������
        Event();
    }

    //  Switch��ON/OFF
    public override void Event()
    {
        //  bool�𔽓]������
        IsPlay = !IsPlay;
        //  �A�j���[�^�[
        m_animator.SetBool("Switch", IsPlay);

        if (IsPlay) m_playGimmick.SwichOn();
        else m_playGimmick.SwichOff();
    }
}
