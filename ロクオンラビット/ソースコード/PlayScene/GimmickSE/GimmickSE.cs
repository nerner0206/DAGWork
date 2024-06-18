using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GimmickSE : Sound
{
    [SerializeField, Tooltip("������������͈�")]
    private float m_listenSoundRange = 5.0f;

    [SerializeField, Tooltip("���̍ő剹��")]
    private float m_maxSound = 1f;

    [SerializeField, Tooltip("audioSource")]
    protected AudioSource m_audioSource;

    //  ���̕������鋗����n��
    public float GetListenSoundRange()
    {
        return m_listenSoundRange;
    }
    //  ���̍ő剹�ʂ�n��
    public float GetMaxSound()
    {
        return m_maxSound;
    }

    public virtual AudioSource GetAudioSource()
    {
        return m_audioSource;
    }

    //  �h�A�̃X�N���v�g�ȊO�������Ȃ�
    public virtual void OnEvent() { }
}
