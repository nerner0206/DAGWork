using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//  ���̎��
public enum SoundKind
{
    Water = 0,          //  ��
    WoodBreak,          //  �ؔj��
    Electric,           //  �d�C
    Fire,               //  ��
    Motor,              //  ���[�^�[
    Door,               //  �h�A
    Swich,              //  �X�C�b�`
    Melt,               //  �n����
    Wind,               //  ��
    Beam,               //  �r�[��
    GlassBreak,         //  �K���X�j��

    Over
}

public class Sound : MonoBehaviour
{
    [SerializeField, Tooltip("���̎��")]
    protected SoundKind m_soundKind;

    //  �n��
    public SoundKind GetSoundKind(){ return m_soundKind; }
    //  ���炤
    public void SetSoundKind(SoundKind sound) { this.m_soundKind = sound; }
}
