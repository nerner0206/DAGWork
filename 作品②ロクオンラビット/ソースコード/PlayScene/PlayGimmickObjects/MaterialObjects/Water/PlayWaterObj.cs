using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class PlayWaterObj : PlayGimmick
{
    [SerializeField, Tooltip("����")]
    private BuoyancyEffector2D m_effector2D;
    [SerializeField, Tooltip("�t��")]
    private GameObject m_playBackWater;
    [SerializeField, Tooltip("����")]
    private TilemapRenderer m_playWater;

    //  �ŏ��̕���
    private float m_startEffector;

    public override void Init()
    {
        m_startEffector = m_effector2D.flowMagnitude;

        if (m_playBackWater != null)
        {
            //  �摜�̕ύX
            m_playWater.enabled = true;
            m_playBackWater.SetActive(false);
        }
    }

    //  �����q�b�g����
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  �q�b�g������
        m_hitSoundKind = kind;

        switch (m_hitSoundKind)
        {
            //  ��
            case SoundKind.Water:
                
                //  �ʏ�Đ��{�t�Đ���
                if (pitch > 0 && m_audioSource.pitch < 0)
                {
                    //  �s�b�`�̕ύX
                    m_audioSource.pitch = pitch;
                    //  �����̔��]
                    m_effector2D.flowMagnitude *= -1f;

                    if (m_playBackWater != null)
                    {
                        //  �摜�̕ύX
                        m_playWater.enabled = true;
                        m_playBackWater.SetActive(false);
                    }
                }
                //  �t�Đ��{�ʏ�Đ���
                else if (pitch < 0 && m_audioSource.pitch > 0)
                {
                    //  �s�b�`�̕ύX
                    m_audioSource.pitch = pitch;
                    //  �����̔��]
                    m_effector2D.flowMagnitude *= -1f;

                    if(m_playBackWater != null)
                    {
                        //  �摜�̕ύX
                        m_playWater.enabled = false;
                        m_playBackWater.SetActive(true);
                    }
                }
                break;

            default:
                break;
        }
    }
    //  �������ꂽ��
    public override void SoundNot()
    {
        m_hitSoundKind = SoundKind.Over;
    }
    //  ���Z�b�g
    public override void GimmickReset()
    {
        m_effector2D.flowMagnitude = m_startEffector;

        if (m_playBackWater != null)
        {
            //  �摜�̕ύX
            m_playWater.enabled = true;
            m_playBackWater.SetActive(false);
        }
    }
}
