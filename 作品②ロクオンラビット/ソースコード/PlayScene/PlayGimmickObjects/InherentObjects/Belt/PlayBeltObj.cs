using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayBeltObj : PlayGimmick
{
    //  ��]����
    private enum RotDir
    {
        Clock,
        UnClock
    }

    [SerializeField, Tooltip("�q�I�u�W�F�N�g�̃X�N���v�g")]
    private BeltConveyor m_beltConveyor;
    [SerializeField, Tooltip("�A�j���[�^�[")]
    private Animator m_animator;

    [SerializeField, Tooltip("�ŏ�����ғ����Ă��邩")]
    private bool m_isMove = false;
    [SerializeField, Tooltip("�f�t�H���g�̉�]����")]
    private RotDir m_defRotDir = RotDir.Clock;

    [SerializeField, Tooltip("�����E���X�N���v�g")]
    private PlayGimmickSE m_playGimmickSE;

    [SerializeField, Tooltip("���x")]
    private float m_moveSpeed = 1.0f;

    //  �������
    private bool m_startMove = false;

    public bool GetSetIsMove
    {
        get { return m_isMove; }
        set { m_isMove = value; }
    }

    //  ������
    public override void Init()
    {
        //  ������
        m_beltConveyor.Init(m_isMove);
        m_playGimmickSE.Init();

        m_startMove = m_isMove;

        //  �ŏ�����ғ���
        if (!m_isMove) return;

        BeltPlay();
    }

    //  ���Z�b�g
    public override void GimmickReset()
    {
        //  �ŏ�����ғ����Ă��Ȃ��Ȃ�~�߂�
        if (!m_startMove) BeltStop();
        //  �ŏ�����ғ����Ă���Ȃ瓮����
        else BeltPlay();
    }

    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ���̎�ނ��擾
        m_hitSoundKind = kind;

        //  �����Ƃ̏���������

        //  ���̎�ނɂ�鏈��
        switch (m_hitSoundKind)
        {
            //  ���[�^�[��
            case SoundKind.Motor:
                //  ���̑��x���擾
                m_audioSource.pitch = pitch;
                //  ����
                HitMotor();
                break;

            //  �������Ȃ�
            default:
                return;
        }
    }

    private void HitMotor()
    {
        //  �~�܂��Ă����瓮����
        if (!m_isMove) BeltPlay();
        //  �f�t�H���g�������v���
        else if(UnClockCheck() && m_defRotDir == RotDir.UnClock)
        {
            //  �x���g�R���x�A�̊p�x
            float angle = gameObject.transform.localEulerAngles.z * Mathf.Deg2Rad;
            //  �X�s�[�h���̍Đ����x
            float picth = m_audioSource.pitch * m_moveSpeed;
            
            //  ���̍Đ����x����A�j���[�V�����̕�����ݒ�
            m_animator.SetFloat("Speed", picth);

            //  �x���g�R���x�A�̉ғ����x��ݒ�
            m_beltConveyor.SetPushDir(angle, -picth);
        }
        //  �f�t�H���g�����v���
        else if(ClockCheck() && m_defRotDir == RotDir.Clock)
        {
            //  �x���g�R���x�A�̊p�x
            float angle = gameObject.transform.localEulerAngles.z * Mathf.Deg2Rad;
            //  �X�s�[�h���̍Đ����x
            float picth = m_audioSource.pitch + m_moveSpeed;

            //  ���̍Đ����x����A�j���[�V�����̕�����ݒ�
            m_animator.SetFloat("Speed", picth);

            //  �x���g�R���x�A�̉ғ����x��ݒ�
            m_beltConveyor.SetPushDir(angle, -picth);
        }
    }

    private bool UnClockCheck()
    {
        if (
            //  �f�t�H���g��] && �t�Đ�
            (m_animator.GetFloat("Speed") > 0f && m_audioSource.pitch < 0f) ||
            //  �t��]�@&&�@���ʍĐ�
            (m_animator.GetFloat("Speed") < 0f && m_audioSource.pitch > 0f))
        {
            return true;
        }
        return false;
    }
    private bool ClockCheck()
    {
        if (
            //  �f�t�H���g��] && �t�Đ�
            (m_animator.GetFloat("Speed") < 0f && m_audioSource.pitch < 0f) ||
            //  �t��]�@&&�@���ʍĐ�
            (m_animator.GetFloat("Speed") > 0f && m_audioSource.pitch > 0f))
        {
            Debug.Log(true);
            return true;
        }
        Debug.Log(false);
        return false;
    }

    //  �x���g�R���x�A���ғ�������
    private void BeltPlay()
    {
        //  �ғ�
        m_isMove = true;
        //  �����E����悤�ɂ���
        m_playGimmickSE.OnGimmickSE(m_soundKind);

        //  �x���g�R���x�A�̊p�x
        float angle = gameObject.transform.localEulerAngles.z * Mathf.Deg2Rad;
        //  �X�s�[�h���̍Đ����x
        float picth = m_audioSource.pitch * m_moveSpeed;

        if (m_defRotDir == RotDir.Clock) picth *= -1.0f;

        //  ���̍Đ����x����A�j���[�V�����̕�����ݒ�
        m_animator.SetFloat("Speed", picth);

        //  �x���g�R���x�A���O��
        m_beltConveyor.GetSetIsOn = true;
        //  �x���g�R���x�A�̉ғ����x��ݒ�
        m_beltConveyor.SetPushDir(angle, -picth);

        //  �����Đ��Đ�����
        m_audioSource.Play();
    }
    //  �x���g�R���x�A���~�߂�
    private void BeltStop()
    {
        //  �ғ�
        m_isMove = false;
        //  �A�j���[�V�����̐ݒ�
        m_animator.SetFloat("Speed", 0.0f);
        //  ��~����
        m_audioSource.Stop();
        //  �����E���Ȃ��悤�ɂ���
        m_playGimmickSE.OffGimmickSE();
        //  �X�N���v�g����~
        m_beltConveyor.GetSetIsOn = false;
    }

    public override void SwichOn()
    {
        BeltPlay();
    }
    public override void SwichOff()
    {
        BeltStop();
    }
}
