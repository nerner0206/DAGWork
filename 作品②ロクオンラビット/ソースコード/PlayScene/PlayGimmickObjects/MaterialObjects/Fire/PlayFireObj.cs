using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayFireObj : PlayGimmick
{
    [SerializeField, Tooltip("���̗̑�")]
    private int m_fireHp = 3;
    [SerializeField, Tooltip("����")]
    private float m_coolTime = 1f;

    [SerializeField, Tooltip("����n���M�~�b�N")]
    private PlayGimmickSE m_playGimmickSE;

    //  �v�Z�p�̗̑�
    private int m_fh = 0;
    //  �f�t�H���g�̃T�C�Y
    private Vector3 m_defScale = Vector3.one;

    //  ����
    private float m_timer;

    //  �����ڐG
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  �G�ꂽ���̎�ނ̎擾
        m_hitSoundKind = kind;

        //  �����̉��ł͓����������̏�����Update���ɏ����̂��f�t�H���g�Ƃ���
    }

    //  �������ꂽ
    public override void SoundNot()
    {
        base.SoundNot();
    }

    //  ���Z�b�g
    public override void GimmickReset()
    {
        //  �����̗͂̐ݒ�
        m_fh = m_fireHp;

        //  �N�[���^�C���̐ݒ�
        m_timer = m_coolTime;

        //  ������
        m_playGimmickSE.Init();
        //  �E�����Ԃɂ���
        m_playGimmickSE.OnGimmickSE(m_soundKind);
        //  �傫���X�V
        gameObject.transform.localScale = m_defScale;
    }

    //  ������
    public override void Init()
    {
        m_fh = m_fireHp;

        m_timer = m_coolTime;
        //  �����T�C�Y���擾
        m_defScale = gameObject.transform.localScale;

        //  ������
        m_playGimmickSE.Init();
        //  �E�����Ԃɂ���
        m_playGimmickSE.OnGimmickSE(m_soundKind);
    }

    //  ���̉����ڐG
    public virtual void HitWater()
    {
        if (m_timer > 0f)
        {
            //  ���Ԃ����炷
            m_timer -= Time.deltaTime;
            //  �����I��
            return;
        }

        //  ���̗̑͂����炷
        m_fh -= 1;
        //  �̗͂��O�ɂȂ�����폜����
        if(m_fh <= 0)
        {
            //  �폜
            gameObject.SetActive(false);
            //  �����I��
            return;
        }

        //  ���Ԃ����Z�b�g
        m_timer = m_coolTime;
        //  �傫����ύX����
        Vector3 s = Vector3.Lerp(Vector3.zero, m_defScale, (float)m_fh / (float)m_fireHp);
        //  �傫���X�V
        gameObject.transform.localScale = s;
    }
}
