using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GimmickSE : Sound
{
    [SerializeField, Tooltip("音が聞こえる範囲")]
    private float m_listenSoundRange = 5.0f;

    [SerializeField, Tooltip("音の最大音量")]
    private float m_maxSound = 1f;

    [SerializeField, Tooltip("audioSource")]
    protected AudioSource m_audioSource;

    //  音の聞こえる距離を渡す
    public float GetListenSoundRange()
    {
        return m_listenSoundRange;
    }
    //  音の最大音量を渡す
    public float GetMaxSound()
    {
        return m_maxSound;
    }

    public virtual AudioSource GetAudioSource()
    {
        return m_audioSource;
    }

    //  ドアのスクリプト以外処理しない
    public virtual void OnEvent() { }
}
