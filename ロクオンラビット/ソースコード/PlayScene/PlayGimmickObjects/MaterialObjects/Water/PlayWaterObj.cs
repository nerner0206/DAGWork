using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class PlayWaterObj : PlayGimmick
{
    [SerializeField, Tooltip("浮力")]
    private BuoyancyEffector2D m_effector2D;
    [SerializeField, Tooltip("逆流")]
    private GameObject m_playBackWater;
    [SerializeField, Tooltip("普通")]
    private TilemapRenderer m_playWater;

    //  最初の浮力
    private float m_startEffector;

    public override void Init()
    {
        m_startEffector = m_effector2D.flowMagnitude;

        if (m_playBackWater != null)
        {
            //  画像の変更
            m_playWater.enabled = true;
            m_playBackWater.SetActive(false);
        }
    }

    //  音がヒットした
    public override void SoundHit(SoundKind kind, float pitch, AudioClip audioClip)
    {
        //  ヒットした音
        m_hitSoundKind = kind;

        switch (m_hitSoundKind)
        {
            //  水
            case SoundKind.Water:
                
                //  通常再生＋逆再生中
                if (pitch > 0 && m_audioSource.pitch < 0)
                {
                    //  ピッチの変更
                    m_audioSource.pitch = pitch;
                    //  水流の反転
                    m_effector2D.flowMagnitude *= -1f;

                    if (m_playBackWater != null)
                    {
                        //  画像の変更
                        m_playWater.enabled = true;
                        m_playBackWater.SetActive(false);
                    }
                }
                //  逆再生＋通常再生中
                else if (pitch < 0 && m_audioSource.pitch > 0)
                {
                    //  ピッチの変更
                    m_audioSource.pitch = pitch;
                    //  水流の反転
                    m_effector2D.flowMagnitude *= -1f;

                    if(m_playBackWater != null)
                    {
                        //  画像の変更
                        m_playWater.enabled = false;
                        m_playBackWater.SetActive(true);
                    }
                }
                break;

            default:
                break;
        }
    }
    //  音が離れたら
    public override void SoundNot()
    {
        m_hitSoundKind = SoundKind.Over;
    }
    //  リセット
    public override void GimmickReset()
    {
        m_effector2D.flowMagnitude = m_startEffector;

        if (m_playBackWater != null)
        {
            //  画像の変更
            m_playWater.enabled = true;
            m_playBackWater.SetActive(false);
        }
    }
}
