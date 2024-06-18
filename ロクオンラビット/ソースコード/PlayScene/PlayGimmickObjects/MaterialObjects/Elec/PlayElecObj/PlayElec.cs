using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayElec : PlayElecObj
{
    [SerializeField, Tooltip("�d��")]
    private ElecLine[] m_lines;

    [SerializeField, Tooltip("�摜")]
    private SpriteRenderer m_spriteRenderer;

    //  �t�Đ�
    private bool m_playback;

    //  ������
    public override void Init()
    {
        //  �d���̏�����
        for (int i = 0; i < m_lines.Length; i++)
        {
            m_lines[i].Init();
        }

        //  �ʏ�Đ�
        m_playback = false;
        m_spriteRenderer.color = new Color(1, 1, 1, 1);
    }

    //  �����ڐG
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  �d�C�ȊO�������Ȃ�
        if (kind != SoundKind.Electric) return;

        m_audioSource.pitch = pitch;

        //  �ʏ��ԁ{�t�Đ�
        if(!m_playback && pitch < 0f)
        {
            foreach (var line in m_lines) line.SetElec();
            m_playback = true;
            m_spriteRenderer.color = new Color(1, 0, 0, 1);
        }
        //  �t�Đ���ԁ{���ʍĐ�
        else if(m_playback && pitch > 0f)
        {
            foreach (var line in m_lines) line.SetElec();
            m_playback = false;
            m_spriteRenderer.color = new Color(1, 1, 1, 1);
        }
    }

    //  ���Z�b�g
    public override void GimmickReset()
    {
        //  �d���̏�����
        for (int i = 0; i < m_lines.Length; i++)
        {
            m_lines[i].Init();
        }

        m_playback = false;
        m_spriteRenderer.color = new Color(1, 1, 1, 1);
    }
}
