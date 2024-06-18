using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class PlayGimmick : Sound
{
    //  AudioSource
    protected AudioSource m_audioSource;
    //  �q�b�g�������̎��
    protected SoundKind m_hitSoundKind;

    //  �n��
    public SoundKind GetIsSoundHit() { return m_hitSoundKind; }
    //  �擾
    public void SetIsSoundHit(SoundKind flag) { m_hitSoundKind = flag; }

    private void Start()
    {
        //  ������
        m_audioSource = gameObject.GetComponent<AudioSource>();

        m_hitSoundKind = SoundKind.Over;
        
        Init();
    }

    //  ������
    public virtual void Init() { }

    //  �����q�b�g����
    public virtual void SoundHit(
        SoundKind kind,         //  ���̎��
        float pitch,          //  �Đ����@
        AudioClip audioClip     //  ���f��
        ) { }

    //  �������ꂽ
    public virtual void SoundNot() 
    {
        //  ��������
        m_hitSoundKind = SoundKind.Over;
    }

    //  ���Z�b�g
    public virtual void GimmickReset() { }

    //  �X�C�b�`�ɂ��On
    public virtual void SwichOn() { }

    //  �X�C�b�`�ɂ��Off
    public virtual void SwichOff() { }

    //  �����蔻��
    public virtual void OnTriggerEnter2D(Collider2D collision)
    {
        //  �����G��Ă��Ȃ�
        if (!collision.gameObject.CompareTag("Sound")) return;

        //  ���̎��
        SoundKind kind = collision.gameObject.gameObject.GetComponent<Sound>().GetSoundKind();

        //  AudioSource���擾
        AudioSource audioSource = collision.gameObject.GetComponent<AudioSource>();

        //  ���̍Đ����@
        float pitch = audioSource.pitch;
        //  ���̑f��
        AudioClip audioClip = audioSource.clip;

        //  �����q�b�g����
        SoundHit(kind, pitch, audioClip);
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        //  �����G��Ă��Ȃ�
        if (!collision.gameObject.CompareTag("Sound")) return;

        SoundNot();
    }
}
