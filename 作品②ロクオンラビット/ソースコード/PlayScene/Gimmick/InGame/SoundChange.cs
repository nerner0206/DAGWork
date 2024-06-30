using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundChange : PlayGimmick
{
    [SerializeField, Tooltip("���f��")]
    private AudioClip[] m_audioClips;
    [SerializeField, Tooltip("�ύX���鉹")]
    private SoundKind[] m_soundKinds;
    [SerializeField, Tooltip("�N���ς�")]
    private bool m_playing = false;
    [SerializeField, Tooltip("�����E���X�N���v�g")]
    private PlayGimmickSE m_playGimmickSE;

    //  �ԍ�
    private int m_num = 0;

    //  �����q�b�g������
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  �q�b�g���������d�C����Ȃ������珈�����Ȃ� || ���ɓ����Ă���
        if (kind != SoundKind.Electric || m_playing) return;

        m_playing = true;
        //  �E����悤�ɂ���
        m_playGimmickSE.OnGimmickSE(m_soundKinds[m_num]);

        //  ���̎�ނ�ݒ�
        m_soundKind = m_soundKinds[m_num];
        //  ����n��
        m_audioSource.clip = m_audioClips[m_num];
        //  �Đ�
        m_audioSource.Play();
    }

    public override void Init()
    {
        m_num = 0;

        m_playGimmickSE.Init();
        m_playGimmickSE.OffGimmickSE();

        if (!m_playing) return;

        //  �E����悤�ɂ���
        m_playGimmickSE.OnGimmickSE(m_soundKinds[m_num]);

        //  ���̎�ނ�ݒ�
        m_soundKind = m_soundKinds[m_num];
        //  ����n��
        m_audioSource.clip = m_audioClips[m_num];
        //  �Đ�
        m_audioSource.Play();
    }

    //  ����ύX����
    public void HitSoundChange()
    {
        if (!m_playing) return;

        //  ���̉���
        m_num++;
        if(m_num >= m_audioClips.Length) m_num = 0; 

        //  ���̎�ނ�ݒ�
        m_soundKind = m_soundKinds[m_num];
        //  �E����悤�ɂ���
        m_playGimmickSE.OnGimmickSE(m_soundKind);
        //  ����n��
        m_audioSource.clip = m_audioClips[m_num];
        //  �Đ�
        m_audioSource.Play();
    }
}
