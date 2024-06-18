using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundIcon : Sound
{
    //  AudioSources
    private AudioSource m_audioSource;

    //  Rigidbody2D
    private Rigidbody2D m_rb2D;
    //  player�̈ʒu
    private Transform m_player;
    //  �Đ���
    private bool m_playBack;
    public bool GetPlayBack() { return m_playBack; }

    //  ������
    public void Init(Transform p, bool playBack, SoundKind kind, AudioClip clip)
    {
        //  ��������
        m_rb2D = gameObject.GetComponent<Rigidbody2D>();
        //  audioSource���擾
        m_audioSource = gameObject.GetComponent<AudioSource>();
        //  player
        m_player = p;

        //  ���̎��
        m_soundKind = kind;
        //  ���̑f��
        m_audioSource.clip = clip;
        //  ����炷
        m_audioSource.Play();

        //  �Đ����@
        this.m_playBack = playBack;
        //  ���ʍĐ�
        if (this.m_playBack) m_audioSource.pitch = 1;
        //  �t�Đ�
        else m_audioSource.pitch = -1;
    }

    private void FixedUpdate()
    {
        //  �ʒu����
        gameObject.transform.position = m_player.position;
    }
}
