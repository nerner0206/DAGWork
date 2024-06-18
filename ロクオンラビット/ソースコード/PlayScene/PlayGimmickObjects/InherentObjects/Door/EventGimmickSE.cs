using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventGimmickSE : PlayGimmickSE
{
    [SerializeField, Tooltip("ドアのスクリプト")]
    private EventGimmick m_eventGimmick;

    public override AudioSource GetAudioSource()
    {
        return base.GetAudioSource();
    }

    public override void OnEvent()
    {
        //  ドアを開く
        m_eventGimmick.Event();
    }
}
